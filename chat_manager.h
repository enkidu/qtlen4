#include <QtCore/QtCore>
#include "qtlenchatcontainer.hpp"
#include "qtlenchatwindow.hpp"
#include "roster_manager.h"
#include "systrayicon.h"
#include "historymanager.hpp"
#include "defines.h"
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
                void                    enableHistory(bool);
	private:
                QList<ChatItem>		chats;
		QString 		myNick;
		QString			myJid;
		QTlenTrayIcon*		sysIcon;
                QTlenChatContainer*     container;
                bool                    useHistory;
	public slots:
		void			showMessage(QString, QString, QDateTime);
		void			detachWidget(QString);
		void			openChat(QString);
		void			setMyInfo(QString, QString);
		void			messageProxy(QString, QString);
		void			typingStarted(QString);
		void			typingStopped(QString);
                       void                                 presenceFrom(QString, QTlenPresence, QString, QString, QString);
                QTlenChatWidget*	createWindow(QString);
                void                    getImage(QString rt, QString idt, QString sender);
                void                    gotImage(QString from, QPixmap image);
                void                    lastMessages(QString, const QList<QTlenMessageStruct>&);
	signals:
		void			sendMessage(QString, QString);
		void			sendTyping(QString, bool);
                void                    infoRequest(QString);
                void                    fetchLastMessages(QString, int);
                void                    saveMessage(const QString&, const QString&, const QString&, const QDateTime&);
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
