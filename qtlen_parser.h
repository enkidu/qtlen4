#ifndef QTLEN_PARSER_H
#define QTLEN_PARSER_H
#include <QtXml>
#include <QtCore>
#include "defines.h"
/*class QTlenParser : public QObject
{
	Q_OBJECT
	public:
		QTlenParser();
                ~QTlenParser(){}
                bool parse(QByteArray input);
		QString sessionId;
	private:
		void readUnknownElement();
		void readSession();
		void readM();
		void readMessage();
		QString readMessageBody();
		QDateTime readMessageDelay();
		void readIq();
		void readRosterQuery();
		void readRosterItem();
		void readVcardQuery();
		void readVcardItem();
		void readSearchQuery();
		void readSearchItem();
		void readMyInfoQuery();
		void readMyInfoItem();
		void readRosterUpdateQuery();
		void readPresence();
		QString decode(QString);
	signals:
		void message(QString, QString, QDateTime);
		void presenceFrom(QString, QTlenPresence, QString);
		void typingStarted(QString);
		void typingStopped(QString);
		void soundAlert(QString);
		void rosterInfoBegin();
		//item: jid, group, name, subscription,
		void rosterItem(QString, QString, QString, QString);
		void authenticated();
		void authorizationError();
		void myInfoArrived(QTlenUserInfo);
		void searchItem(QTlenUserInfo);
		void autorizationRequest(QString);
		void vcardArrived(QTlenUserInfo);
		void connected();
};*/

int calc_passcode(const char* pass, char* code);
char *tlen_hash (const char *pass, const char *id);
char *urlencode(const char *msg);
char *urldecode(const char *str);
char hextochar(const char *str);
#endif
