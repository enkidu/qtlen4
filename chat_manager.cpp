#include "chat_manager.h"

QTlenChatManager::QTlenChatManager(QTlenRosterManager * roster, QTlenHistoryManager * history)
{
	this->roster = roster;
        this->history = history;
        container = new QTlenChatContainer(0,0);
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
            container->startBlinking();
	ChatItem i;
	i.jid = jid;
        QTlenChatWidget *widget = container->addChat();
        container->setTabText(widget, roster->getNameOf(jid));
	widget->setContactInfo(jid, roster->getNameOf(jid));
	widget->setMyInfo(myNick);
        //widget->show();
	widget->showPreviousMessages(history->getLastMessages(jid, 10));
	i.widget=widget;
	chats.append(i);
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
                    container->startBlinking();
		history->saveMessage(jid, myJid, body, stamp);
	}
	else
	{
		sysIcon->showMessage(tr("New chat with ") + roster->getNameOf(jid), body);
                QTlenChatWidget *widget = createWindow(jid);
		history->saveMessage(jid, myJid, body,  stamp);
		widget->showMessage(body, stamp);
                container->startBlinking();
		widget->setTyping(false);
	}
}

void QTlenChatManager::detachWidget(const QString jid)
{
    qDebug("called QTlenChatManager::detachWidget");
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
	history->saveMessage(myJid, jid, body, QDateTime::currentDateTime());
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
        qDebug("GET " +request.toAscii());
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
            else
            {
                qDebug("Wrong pixmap");
                qDebug(data);
            }
        }
}
