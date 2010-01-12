#include "chat_manager.h"
#include <QIcon>
QTlenChatManager::QTlenChatManager(QTlenRosterManager * roster, QTlenHistoryManager * history)
{
	this->roster = roster;
        this->history = history;
        container = new QTlenChatContainer(0,0);
        useHistory = true;
}

int QTlenChatManager::findIndexOf(QString jid)
{
	for ( int n = 0; n < (int)chats.count(); n++ )
		if( chats[n].jid == jid )
			return n;
	return -1;
}

QTlenChatWidget* QTlenChatManager::createWindow(QString jid)
{
            container->show();
        if (!container->isActiveWindow())
        {
            container->startBlinking();
            container->raise();
        }
	ChatItem i;
        i.jid = jid;
        RosterItem item = roster->getRosterItem(jid);
        QTlenChatWidget *widget = container->addChat();
        container->setTabText(widget, item.name);
        widget->setContactInfo(jid, item.name);
	widget->setMyInfo(myNick);
        //widget->show();

	i.widget=widget;
	chats.append(i);
        if (useHistory)
            emit fetchLastMessages(jid, 10);
        QIcon icon;
        switch (item.presence)
        {
            case Online:
                icon.addPixmap(QPixmap(QString::fromUtf8(":/icons/icons/16x16/online.png")));
                break;
            case Chatty:
                icon.addPixmap(QPixmap(QString::fromUtf8(":/icons/icons/16x16/chatty.png")));
                break;
            case Away:
                icon.addPixmap(QPixmap(QString::fromUtf8(":/icons/icons/16x16/away.png")));
                break;
            case XA:
                icon.addPixmap(QPixmap(QString::fromUtf8(":/icons/icons/16x16/xa.png")));
                break;
            case DND:
                icon.addPixmap(QPixmap(QString::fromUtf8(":/icons/icons/16x16/dnd.png")));
                break;
            case Offline:
                icon.addPixmap(QPixmap(QString::fromUtf8(":/icons/icons/16x16/offline.png")));
                break;
        }
        int index = findIndexOf(jid);
        container->tabbar->setTabIcon(index, icon);
        if (chats.count() == 1)
        {
            container->setWindowIcon(icon);
            container->icon = icon;
        }

        connect(widget,
                SIGNAL(widgetClosed(QString)),
                this,
                SLOT(detachWidget(QString)));
        connect(widget,
                SIGNAL(message(QString, QString)),
                this,
                SLOT(messageProxy(QString, QString)));
        connect(widget,
                SIGNAL(typing(QString,bool)),
                this,
                SIGNAL(sendTyping(QString,bool)));
        connect(widget,
                SIGNAL(infoRequest(QString)),
                this,
                SIGNAL(infoRequest(QString)));
        return widget;
}

void QTlenChatManager::showMessage(QString jid, QString body, QDateTime stamp)
{
    int index = findIndexOf(jid);
	if (index != -1)
	{
		chats[index].widget->showMessage(body, stamp);
                if (chats[index].widget != container->stack->currentWidget())
                {
                    container->setTabColour(chats[index].widget, QColor::QColor("#f00"));
                }
                if (!container->isActiveWindow())
		{
                    container->increasePendingMessages();
                    container->startBlinking();
                    container->raise();

		}
                if (useHistory)
                    emit saveMessage(jid, myJid, body, stamp);
	}
	else
	{
		sysIcon->showMessage(tr("New chat with ") + roster->getNameOf(jid), body);
                QTlenChatWidget *widget = createWindow(jid);
                if (useHistory)
                    emit saveMessage(jid, myJid, body,  stamp);
		widget->showMessage(body, stamp);
                container->increasePendingMessages();
                container->startBlinking();
		widget->setTyping(false);
	}
}

void QTlenChatManager::detachWidget(const QString jid)
{
    int index = findIndexOf(jid);
	if (index != -1)
	{
	    chats[index].widget->disconnect();
	    chats.removeAt(index);
	}
    if (container->tabbar->count() == 1)
        container->hide();
}

void QTlenChatManager::openChat(QString jid)
{
	if ((findIndexOf(jid) == -1) and jid != "-1")
	{
		createWindow(jid);
	}
}

void QTlenChatManager::typingStarted(QString jid)
{
	if (findIndexOf(jid) != -1)
                container->setTabColour(chats[findIndexOf(jid)].widget, QColor::QColor("#0a0"));
	else
	{
		sysIcon->showMessage(tr("New chat with ") + roster->getNameOf(jid), QString("..."));
                QTlenChatWidget *widget = createWindow(jid);
		widget->setTyping(true);
	}
}

void QTlenChatManager::typingStopped(QString jid)
{
	if (findIndexOf(jid) != -1)
                container->setTabColour(chats[findIndexOf(jid)].widget, QColor::QColor("#000"));
}

void QTlenChatManager::setMyInfo(QString nick, QString jid)
{
	myNick = nick; //może pobierać to ze wskaźnika do ustawień?
	myJid = jid;
}

void QTlenChatManager::messageProxy(QString jid, QString body)
{
    emit sendMessage(jid, body);
    if (useHistory)
        emit saveMessage(myJid, jid, body, QDateTime::currentDateTime());
}

QTlenImageFetcher::QTlenImageFetcher()
{
}

void QTlenImageFetcher::getImage(QString rt, QString idt, QString sender, QString jid)
{
    this->rt = rt;
    this->idt = idt;
    this->sender = sender;
    this->jid = jid;
    this->first = true;
    http = new QTcpSocket();
        QString request = "<pic auth='"+jid+"' t='g' from='"+sender+"' pid='1001' rt='"+rt+"' idt='"+idt+"'/>";
        http->connectToHost("ps.tlen.pl", 443);
        http->write(request.toAscii());
        connect(http, SIGNAL(readyRead()), this, SLOT(getPart()));
}

void QTlenChatManager::getImage(QString rt, QString idt, QString sender)
{
    QTlenImageFetcher * fetcher = new QTlenImageFetcher();
    connect(fetcher,
            SIGNAL(gotImage(QString,QPixmap)),
            this,
            SLOT(gotImage(QString,QPixmap)));
    fetcher->getImage(rt, idt, sender, this->myJid);
}

void QTlenChatManager::gotImage(QString from, QPixmap image)
{
        int index = findIndexOf(from);
        if (index != -1)
        {
                chats[index].widget->showImage(image);
                if (!chats[index].widget->isActiveWindow())
                    container->startBlinking();
                /*        sysIcon->showMessage(tr("Message from ") + roster->getNameOf(jid), body);
                chats[index].widget->raise();*/
                //history->saveMessage(jid, myJid, body, stamp);
        }
        else
        {
                /*sysIcon->showMessage(tr("New chat with ") + roster->getNameOf(jid), body);*/
                QTlenChatWidget *widget = createWindow(from);
                //history->saveMessage(jid, myJid, body,  stamp);
                widget->showImage(image);
                widget->setTyping(false);
        }
}

void QTlenChatManager::lastMessages(QString r_jid, const QList<QTlenMessageStruct> &list)
{
    int index = findIndexOf(r_jid);
    if (index != -1)
    {
        chats[index].widget->showPreviousMessages(list);
    }
}

void QTlenChatManager::enableHistory(bool ok)
{
    this->useHistory = ok;
}

void QTlenChatManager::presenceFrom(QString jid, QTlenPresence type, QString, QString, QString)
{
    int index = findIndexOf(jid);
    if (index != -1)
    {
        QIcon icon;
        switch (type)
        {
            case Online:
                icon.addPixmap(QPixmap(QString::fromUtf8(":/icons/icons/16x16/online.png")));
                break;
            case Chatty:
                icon.addPixmap(QPixmap(QString::fromUtf8(":/icons/icons/16x16/chatty.png")));
                break;
            case Away:
                icon.addPixmap(QPixmap(QString::fromUtf8(":/icons/icons/16x16/away.png")));
                break;
            case XA:
                icon.addPixmap(QPixmap(QString::fromUtf8(":/icons/icons/16x16/xa.png")));
                break;
            case DND:
                icon.addPixmap(QPixmap(QString::fromUtf8(":/icons/icons/16x16/dnd.png")));
                break;
            case Offline:
                icon.addPixmap(QPixmap(QString::fromUtf8(":/icons/icons/16x16/offline.png")));
                break;
        }
        container->tabbar->setTabIcon(index, icon);
        if (index == container->tabbar->currentIndex())
            container->setWindowIcon(icon);
    }
}

void QTlenImageFetcher::getPart()
{
        QByteArray data = http->readAll();
        if (first)
        {
            first = false;
            int i = data.indexOf(">");
            QByteArray header = data.left(i);
            int j = header.indexOf("'");
            int k = header.indexOf("'", j+1);
            size = header.mid(j+1, k-j-1).toInt();
            data = data.mid(i+1);
        }
        cache.append(data);
        if (cache.size() == size)
        {
            QPixmap raw;
            if (raw.loadFromData(cache))
            {
                emit gotImage(sender, raw);
            }
        }
}
