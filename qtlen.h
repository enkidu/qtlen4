#include <QtNetwork>
#include <QAbstractSocket>
#include <QtXml>
#include <QTimer>
#include <QDateTime>
#include "defines.h"
#include "qtlen_parser.h"
class QTlen: public QObject
{
	Q_OBJECT
	public:
		QTlen();
                ~QTlen(){}
		void setUserParams(QString, QString);
		//QTlenParser	*parser;
		bool		is_connected();
	private:
		bool		isConnected;
		quint16		port;
		QString		username;
		QString		password;
		QString		server;
		QString		remote;
		QString		sessionId;
		QString		hash;
                QString         token;
		QByteArray	cache;
		QHttp		*http;
		QTcpSocket	*socket;
		QString		decode(QString);
		QByteArray	encode(QString);
		QByteArray	tlenHash(QString, QString);
                QTlenMailConfig mailConfig;
	signals:
		void		connecting();
		void		connected();
		void		disconnected();
		//message from body timestamp
		void		message(QString, QString, QDateTime);
		void		typingStarted(QString);
		void		typingStopped(QString);
		void		soundAlert(QString);
		void		rosterInfoBegin();
		//item: jid, group, name, subscription,
		void		rosterItem(QString, QString, QString, QString);
		//presence: from, type, desc
		void		rosterInfoEnd();
		void		presenceFrom(QString, QTlenPresence, QString, QString, QString);
		void		autorizationRequest(QString);
		void		authenticated();
		void		socketError(QAbstractSocket::SocketError);
		void		startPing();
		void		serverConnect();
		void		parse(QByteArray);
		void		receivedXml(QByteArray);
		void		startConnection();
		void		vcardArrived(QTlenUserInfo);
		void		myInfoArrived(QTlenUserInfo);
		void		searchItem(QTlenUserInfo);
		void		searchResultBegin(bool);
// 		wrong username or password
		void		authorizationError();
                void            receivedMailConfig(QTlenMailConfig);
		void		receivedToken(QString);
		void		readyToGetRoster();
	public slots:
		void		makeConnection();
		void		sendMessage(QString, QString);
		void		sendRawXML(QString);
		void		destroyConnection();
		void		getInfoAboutMyself();
		void 		setStatus(int, QString);
		void		setSubscribed(QString, bool);
		void		getInfoAbout(QString);
		void		deleteUser(QString);
		void		chatsGetTopLevelGroups();
		void 		saveRosterItem(QString, QString, QString);
		void		saveMyInfo(QTlenUserInfo);
		void		searchUsers(QTlenUserInfo);
		void		writeLoginString();
		void		writeTyping(QString, bool);
	private slots:
		void		openConnection();
		void		readServerInfo();
		void		checkResponse();
		void		parseResponse(QByteArray input);
		void		getRoster();
		void		getMailInfo();
		void		pinguj();
                void            parseMailConfig(QDomNode);
};

//int calc_passcode(const char* pass, char* code);
//char *tlen_hash (const char *pass, const char *id);
//char *urlencode(const char *msg);
//char *urldecode(const char *str);
//char hextochar(const char *str);
