#include <QtCore/QtCore>
#include "widgets/qtlenchatwindow.hpp"
#include "roster_manager.h"
#include "systrayicon.h"
#include "historymanager.hpp"
class QTlenChatManager: public QObject
{
	Q_OBJECT
	public:
		QTlenChatManager(QTlenRosterManager * roster, QTlenHistoryManager * history);
		~QTlenChatManager(){}
		struct ChatItem
		{
			QString 		jid;
			QTlenChatWindow		*widget;
		};
		int			findIndexOf(QString);
		void			setTrayIcon(QTlenTrayIcon* icon){this->sysIcon = icon;}
		QTlenRosterManager	*roster;
		QTlenHistoryManager	*history;
	private:
		QList<ChatItem>		chats;
		QString 		myNick;
		QString			myJid;
		QTlenTrayIcon*		sysIcon;

	public slots:
		void			showMessage(QString, QString, QDateTime);
		void			detachWidget(QString);
		void			openChat(QString);
		void			setMyInfo(QString, QString);
		void			messageProxy(QString, QString);
		void			typingStarted(QString);
		void			typingStopped(QString);
		QTlenChatWindow*	createWindow(QString);
	signals:
		void			sendMessage(QString, QString);
		void			sendTyping(QString, bool);
};
