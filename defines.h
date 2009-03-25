#ifndef DEFINES_H
#define DEFINES_H
#include <QtCore>
enum QTlenPresence
{
	Online,
	Chatty,
	Away,
	XA,
	DND,
	Invisible, //probably we won't see such an user, but we can set it for ourselves
	Offline
};
enum QTlenSubscription
{
	Both,
	From,
	To,
	None
};
struct QTlenUserInfo
{
	QString		jid;
	QString		first;
	QString		last;
	QString		nick;
	QString		email;
	QString		city;
	QString		school;
	int		year;
	int		sex;
	int		job;
	int		lookingFor;
	bool		visible;	//used for user profile editing
	int		years_from;		//dunno, if we will use that;
	int		years_to;
	int		presence;
	int		start;
};
struct QTlenSettingsChange
{
        bool            user;
        bool            roster;
};

struct QTlenMailConfig
{
        QString         baseUrl;
        QString         msgUrl;
        QString         msgMethod;
        QString         msgIndexUrl;
        QString         msgIndexMethod;
        QString         loginUrl;
        QString         loginMethod;
        QString         logoutUrl;
        QString         logoutMethod;
        QString         compuseUrl;
        QString         composeMethod;
        QString         avatarGetUrl;
        QString         avatarGetMethod;
        QString         avatarSetUrl;
        QString         avatarSetMethod;
        QString         avatarRemoveUrl;
        QString         avatarRemoveMethod;
};

struct QTlenMessageStruct
{
	QString		sent_by;
	QString		sent_to;
	QString		body;
	QDateTime	dateTime;
};
#endif
