#include "qtlenpublicchatsmanager.hpp"
QTlenPublicChatsManager::QTlenPublicChatsManager(QObject * parent): QObject(parent)
{
    window = new QTlenPublicChatsWindow();
    connect(window->mainPage,
            SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),
            this,
            SLOT(handleDoubleClick(QTreeWidgetItem*,int)));
    connect(this,
            SIGNAL(openPublicChat(QString)),
            window,
            SLOT(openPublicChats(QString)));
    connect(window->tabWidget,
            SIGNAL(tabCloseRequested(int)),
            this,
            SLOT(closePage(int)));
}

void QTlenPublicChatsManager::appendList(QString parent, QList<ChatRoomNode> list)
{
    if (parent == "0")
        for(int i =0; i< list.size(); i++)
        {
            QTreeWidgetItem* item = new QTreeWidgetItem(window->mainPage);
            ChatRoomNode n = list[i];
            item->setText(0, n.name);
            item->setText(1, parent + " " + n.id);
                window->mainPage->addTopLevelItem(item);
            n.item = item;
            roomList.append(n);
        }
    else
    {
        QTreeWidgetItem* p = findItem(parent);
        if (p != 0)
        for(int i =0; i< list.size(); i++)
        {
            QTreeWidgetItem* item = new QTreeWidgetItem(p);
            ChatRoomNode n = list[i];
            item->setText(0, n.name);
            item->setText(1, QString::number(n.users));
            p->addChild(item);
            n.item = item;
            roomList.append(n);
        }
    }
}

QTreeWidgetItem* QTlenPublicChatsManager::findItem(QString id) const
{
    for(int i = 0; i < roomList.size(); i++)
    {
        if (roomList[i].id == id)
        {
            return roomList[i].item;
        }
    }
    return 0;
}

ChatRoomNode QTlenPublicChatsManager::findNodeByItem(QTreeWidgetItem *item) const
{
    for(int i = 0; i < roomList.size(); i++)
    {
        if (roomList[i].item == item)
        {
            return roomList[i];
        }
    }
    return ChatRoomNode();
}

void QTlenPublicChatsManager::handleDoubleClick(QTreeWidgetItem* item, int)
{
    ChatRoomNode node = findNodeByItem(item);
    if (node.flags & 0x02)
    {
        if (node.item->childCount() == 0)
            emit expandNode(node.id);
    }
    else if(!isOpenChat(node.id))
    {
        ChatItem i;
        i.id = node.id;
        //tu otworzymy sobie kartę z czatem i zapiszemy wskaźnik
        i.widget = new QTlenPublicChatWidget();
        activeChats.append(i);
        i.widget->setRoomId(node.id);
        window->tabWidget->addTab(i.widget, node.name);
        connect(i.widget,
                SIGNAL(message(QString,QString)),
                this,
                SIGNAL(message(QString,QString)));
        connect(i.widget,
                SIGNAL(startPriv(QString)),
                this,
                SLOT(openPriv(QString)));
        emit openPublicChat(node.id);
    }
}

bool QTlenPublicChatsManager::isOpenChat(QString id) const
{
    for (int i = 0; i < activeChats.size(); i++)
        if (activeChats[i].id == id)
            return true;
    return false;
}

bool QTlenPublicChatsManager::isOpenPriv(QString id) const
{
    for (int i = 0; i < activePrivs.size(); i++)
        if (activePrivs[i].id == id)
            return true;
    return false;
}

void QTlenPublicChatsManager::message(QString chat,
                                      QString user,
                                      QString body,
                                      QString type)
{
    if (type == "o")
    {
        ChatItem item = findItemById(chat);
        if (item.widget != 0)
            item.widget->appendMessage(user, body);
    }
    else
    {
        PrivItem i =findPrivById(chat + "/" + user);
        if (i.widget !=0)
        {
            i.widget->showMessage(body, QDateTime::currentDateTime());
        }
        else
        {
            i.widget = new QTlenChatWidget();
            i.widget->setContactInfo(i.id, user);
            connect(i.widget,
                    SIGNAL(message(QString,QString)),
                    this,
                    SIGNAL(message(QString,QString)));
            i.widget->showMessage(body, QDateTime::currentDateTime());
            window->tabWidget->addTab(i.widget, user);
            i.widget;
            activePrivs.append(i);
        }
    }
}

PrivItem QTlenPublicChatsManager::findPrivById(QString id) const
{
    for (int i = 0; i < activePrivs.size(); i++)
        if (activePrivs[i].id == id)
            return activePrivs[i];
    PrivItem item;
    item.widget = 0;
    item.id = id;
    return item;
}

void QTlenPublicChatsManager::presence(QString chat,
                                       QString user,
                                       int a,
                                       bool ok)
{
    ChatItem item = findItemById(chat);
    if (item.widget != 0)
        item.widget->presence(user,a, ok);
}

QString QTlenPublicChatsManager::findIdByItem(QTlenPublicChatWidget* w) const
{
    for (int i = 0; i < activeChats.size(); i++)
        if (activeChats[i].widget == w)
            return activeChats[i].id;
    return "";
}

ChatItem QTlenPublicChatsManager::findItemById(QString id) const
{
    for (int i = 0; i < activeChats.size(); i++)
        if (activeChats[i].id == id)
            return activeChats[i];
    ChatItem item;
    item.widget = 0;
    return item;
}

void QTlenPublicChatsManager::showWindow()
{
    window->show();
}

void QTlenPublicChatsManager::closePage(int id)
{
    if (id!=0)
    {
        QTlenPublicChatWidget* w = qobject_cast<QTlenPublicChatWidget *>(window->tabWidget->widget(id));
        if (w != 0)
        {
        int index = findIndexOfChat(w);
        if (index != -1)
        {
            emit leaveChatroom(activeChats.at(index).id);
            window->tabWidget->removeTab(id);
            activeChats.removeAt(index);
            w->close();
        }
        }
        else
        {
            QTlenChatWidget* v = qobject_cast<QTlenChatWidget *>(window->tabWidget->widget(id));
            if (v != 0)
            {
            int index = findIndexOfPriv(v);
            if (index != -1)
            {
                activePrivs.removeAt(index);
                window->tabWidget->removeTab(id);
                v->close();
            }
            }
        }
    }
    else
    {
        window->mainPage->clear();
        roomList.clear();
        emit getTopLevel();
    }
}

int QTlenPublicChatsManager::findIndexOfChat(QTlenPublicChatWidget* w) const
{
    for (int i = 0; i < activeChats.size(); i++)
        if (activeChats[i].widget == w)
            return i;
return -1;
}

int QTlenPublicChatsManager::findIndexOfPriv(QTlenChatWidget* w) const
{
    for (int i = 0; i < activePrivs.size(); i++)
        if (activePrivs[i].widget == w)
            return i;
return -1;
}

void QTlenPublicChatsManager::openPriv(QString id)
{
        PrivItem i =findPrivById(id);
        if (i.widget ==0)
        {
            i.widget = new QTlenChatWidget();
            i.widget->setContactInfo(i.id, id);
            connect(i.widget,
                    SIGNAL(message(QString,QString)),
                    this,
                    SIGNAL(message(QString,QString)));
            window->tabWidget->addTab(i.widget, id);
            i.widget;
            activePrivs.append(i);
        }
}
