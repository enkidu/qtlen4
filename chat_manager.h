#include <QtCore/QtCore>
#include "qtlenchatcontainer.hpp"
#include "qtlenchatwindow.hpp"
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
                        QTlenChatWidget		*widget;
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
                QTlenChatContainer*     container;
	public slots:
		void			showMessage(QString, QString, QDateTime);
		void			detachWidget(QString);
		void			openChat(QString);
		void			setMyInfo(QString, QString);
		void			messageProxy(QString, QString);
		void			typingStarted(QString);
		void			typingStopped(QString);
                QTlenChatWidget*	createWindow(QString);
                void                    getImage(QString rt, QString idt, QString sender);
                void                    gotImage(QString from, QPixmap image);
	signals:
		void			sendMessage(QString, QString);
		void			sendTyping(QString, bool);
                void                    infoRequest(QString);
};

class QTlenImageFetcher : public QObject
{
    Q_OBJECT
    public:
        QTlenImageFetcher();
        ~QTlenImageFetcher() {}
    public slots:
        void getImage(QString rt, QString idt, QString sender, QString jid);
    private slots:
        void getPart();
    private:
        QTcpSocket* http;
        QString rt;
        QString idt;
        QString sender;
        QString jid;
        QByteArray cache;
        bool first;
        int size;
    signals:
        void gotImage(QString, QPixmap);
};
