#include "chat_manager.h"

QTlenChatManager::QTlenChatManager(QTlenRosterManager * roster, QTlenHistoryManager * history)
{
	this->roster = roster;
	this->history = history;
}

int QTlenChatManager::findIndexOf(QString jid)
{
	for ( int n = 0; n < (int)chats.count(); n++ )
		if( chats[n].jid == jid )
			return n;
	return -1;
}

QTlenChatWindow* QTlenChatManager::createWindow(QString jid)
{
	ChatItem i;
	i.jid = jid;
	QTlenChatWindow *widget = new QTlenChatWindow();
	widget->setContactInfo(jid, roster->getNameOf(jid));
	widget->setMyInfo(myNick);
	widget->show();
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
	return widget;
}

void QTlenChatManager::showMessage(QString jid, QString body, QDateTime stamp)
{
    int index = findIndexOf(jid);
	if (index != -1)
	{
		chats[index].widget->showMessage(body, stamp);
		if (!chats[index].widget->isActiveWindow())
			sysIcon->showMessage(QString::fromUtf8("Wiadomość od ") + roster->getNameOf(jid), body);
		chats[index].widget->raise();
		history->saveMessage(jid, myJid, body, stamp);
	}
	else
	{
		sysIcon->showMessage(QString::fromUtf8("Nowa rozmowa z ") + roster->getNameOf(jid), body);
		QTlenChatWindow *widget = createWindow(jid);
		history->saveMessage(jid, myJid, body,  stamp);
		widget->showMessage(body, stamp);
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
		chats[findIndexOf(jid)].widget->setTyping(true);
	else
	{
		sysIcon->showMessage(QString::fromUtf8("Nowa rozmowa z ") + roster->getNameOf(jid), QString("..."));
		QTlenChatWindow *widget = createWindow(jid);
		widget->setTyping(true);
	}
}

void QTlenChatManager::typingStopped(QString jid)
{
	if (findIndexOf(jid) != -1)
		chats[findIndexOf(jid)].widget->setTyping(false);
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
