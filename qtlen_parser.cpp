#include "qtlen_parser.h"

/*QTlenParser::QTlenParser(): QObject()
{
}*/
/*QTlenParser::parse(QByteArray input)
{
        //debug, żeby sobie poczytać, o czym gada z nami serwer
        emit receivedXml(input);
        //profilaktycznie puszczamy pinga
        socket->write("  \t  ");
        QDomDocument doc("");
        //brzydka sztuczka, konieczna do poradzenia sobie z nawałem śmiecia w jednym pakiecie
        doc.setContent("<package>"+input+"</package>");
        QDomElement root = doc.documentElement();
        QDomNode node = root.firstChild();
        while (!node.isNull())
        {
                if (node.nodeName() == "s")
                {
                }
                //tu pobieramy token do odczytywania avatarów
                else if (node.nodeName() == "avatar")
                {
                }
                //ktoś pisze lub cyka dzwonkiem (jak śmie!!))
                else if (node.nodeName() == "m")
                {
                }
                //SPAAAAM!
                else if (node.nodeName() == "message")
                {
                }
                //romanse z serwerem
                else if (node.nodeName() == "iq")
                {
                }
                //ktoś wylazł z nory
                else if (node.nodeName() == "presence")
                {
                }
                node=node.nextSibling();
        }
}

                if (node.nodeName() == "s")
                {
                        sessionId=node.toElement().attribute("i","");
                        emit connected();
                        QByteArray loginString("<iq type=\"set\" id=\""+sessionId.toAscii()+"\"><query xmlns=\"jabber:iq:auth\"><username>"+username.toAscii()+"</username><digest>"+tlenHash(password, sessionId)+"</digest><resource>QTlen4</resource><host>tlen.pl</host></query></iq>");
                        socket->write(loginString);
                }
                //tu pobieramy token do odczytywania avatarów
                else if (node.nodeName() == "avatar")
                {
                        token = node.toElement().namedItem("token").toElement().text();
                        emit receivedToken(token);
                }
                //ktoś pisze lub cyka dzwonkiem (jak śmie!!))
                else if (node.nodeName() == "m")
                {
                    if (node.toElement().hasAttribute("tp") and (node.toElement().attribute("tp", "") != "p"))
                    {
                        if (node.toElement().attribute("tp", "") == "t")
                                emit typingStarted(node.toElement().attribute("f", ""));
                        else if (node.toElement().attribute("tp", "") == "u")
                                emit typingStopped(node.toElement().attribute("f", ""));
                        else if (node.toElement().attribute("tp", "") == "a")
                                emit soundAlert(node.toElement().attribute("f", ""));
                    }
                    // jak nie powiadomienia, to czaty

        <m f='261@c/~Pretorius'><b n='6' f='0' c='000000' s='10'>witaj+:D</b></m>

        n - font style (?)
        f - font family
        c - font color
        s - font size
        <b>msg body</b>

        if <m> contains tp='p', it's a private message

                    else
                    {
                        QString from = node.toElement().attribute("f");
                        QDomElement e_body = node.toElement().namedItem("b").toElement();
                        QString color = e_body.attribute("c").prepend("#");
                        int size = e_body.attribute("s").toInt();
                        QString body = e_body.text();
                    }
                }
                //SPAAAAM!
                else if (node.nodeName() == "message")
                {
                        QDateTime datetime = QDateTime::currentDateTime();
                        QString sender = node.toElement().attribute("from", "");
                        emit typingStopped(sender);
                        //QDomNode n = node.toElement().firstChild();
                        QString msg = decode(node.toElement().namedItem("body").toElement().text());
                        if (!node.toElement().namedItem("x").isNull())
                                {
                                        if (node.toElement().namedItem("x").toElement().attribute("xmlns", "") == "jabber:x:delay")
                                                {
                                                        //obliczamy stampa
                                                        //stamp='20090125T19:48:40'
                                                        QString stamp = node.toElement().namedItem("x").toElement().attribute("stamp", "");
                                                        int year = stamp.mid( 0, 4 ).toInt();
                                                        int month = stamp.mid( 4, 2 ).toInt();
                                                        int day = stamp.mid( 6, 2 ).toInt();
                                                        int hour = stamp.mid( 9, 2 ).toInt();
                                                        int min = stamp.mid( 12, 2 ).toInt();
                                                        int sec = stamp.mid( 15, 2 ).toInt();
                                                        datetime.setDate( QDate( year, month, day ) );
                                                        datetime.setTime( QTime( hour, min, sec ) );
                                                }
                                }
                        if (sender != "b73@tlen.pl") //nie potrzebujemy spamu
                                emit message(sender, msg, datetime);
                }
                //romanse z serwerem
                else if (node.nodeName() == "iq")
                {
                        //może to z telewizji? nie, jednak z czata
                        if (node.toElement().attribute("from") == "c")
                        {
                        }
                        //jak nie z czata, to i tak się przyjrzymy
                        else
                        {
                                if (node.toElement().attribute("id", "") == "GetRoster")
                                {
                                        emit rosterInfoBegin();
                                        QDomElement e = node.toElement();
                                        QDomNode n = e.firstChild().toElement().firstChild();
                                        QString group("");
                                        while (!n.isNull())
                                        {
                                                if (n.isElement())
                                                {
                                                        QDomElement ee = n.toElement();
                                                        if (ee.tagName() == "item")
                                                        {
                                                                if(!ee.namedItem("group").isNull())
                                                                        group = decode(ee.namedItem("group").toElement().text());
                                                                else
                                                                        group = "";
                                                                emit rosterItem(ee.attribute("jid", ""), group, decode(ee.attribute("name", "")), ee.attribute("subscription"));
                                                                if (ee.attribute("subscription") == "from" and !ee.hasAttribute("ask"))
                                                                        emit autorizationRequest(ee.attribute("jid", ""));
                                                        }
                                                }
                                                n = n.nextSibling();
                                        }
                                        emit rosterInfoEnd();
                                }
                                else if (node.toElement().attribute("type", "") == "result")
                                {
                                        if (node.toElement().attribute("id", "") == sessionId) //type = error to błąd logowania
                                        {
                                            if (node.toElement().attribute("from", "") == "tcfg")
                                            {
                                                    parseMailConfig(node.toElement().firstChild().toElement().firstChild());
                                            }
                                            else
                                            {
                                                isConnected = true;
                                                emit authenticated();
                                            }
                                        }
                                        else if (node.toElement().attribute("id", "") == "src3@abcd")
                                        {
                                                QDomNode n = node.toElement().namedItem("query").toElement().firstChild();
                                                if(!n.isNull())
                                                {
                                                        QDomElement e = n.toElement();
                                                        QTlenUserInfo info;
                                                        info.jid	= e.attribute("jid");
                                                        info.first	= decode(e.namedItem("first").toElement().text());
                                                        info.last	= decode(e.namedItem("last").toElement().text());
                                                        info.nick	= decode(e.namedItem("nick").toElement().text());
                                                        info.email	= decode(e.namedItem("email").toElement().text());
                                                        info.city	= decode(e.namedItem("c").toElement().text());
                                                        info.school	= decode(e.namedItem("e").toElement().text());
                                                        info.job	= e.namedItem("j").toElement().text().toInt();
                                                        info.lookingFor	= e.namedItem("r").toElement().text().toInt();
                                                        info.sex	= e.namedItem("s").toElement().text().toInt();
                                                        info.year	= e.namedItem("b").toElement().text().toInt();
                                                        emit vcardArrived(info);
                                                }
                                        }
                                        else if (node.toElement().attribute("id", "") == "src")
                                        {
                                                QDomNode n = node.toElement().namedItem("query").toElement().firstChild();
                                                emit searchResultBegin(!n.isNull());
                                                while(!n.isNull())
                                                {
                                                        QDomElement e = n.toElement();
                                                        QTlenUserInfo info;
                                                        info.jid	= e.attribute("jid") + QString("@tlen.pl");
                                                        info.first	= decode(e.namedItem("first").toElement().text());
                                                        info.last	= decode(e.namedItem("last").toElement().text());
                                                        info.nick	= decode(e.namedItem("nick").toElement().text());
                                                        info.email	= decode(e.namedItem("email").toElement().text());
                                                        info.city	= decode(e.namedItem("c").toElement().text());
                                                        info.school	= decode(e.namedItem("e").toElement().text());
                                                        info.job	= e.namedItem("j").toElement().text().toInt();
                                                        info.lookingFor	= e.namedItem("r").toElement().text().toInt();
                                                        info.sex	= e.namedItem("s").toElement().text().toInt();
                                                        info.year	= e.namedItem("b").toElement().text().toInt();
                                                        info.presence	= e.namedItem("a").toElement().text().toInt();
                                                        info.visible	= (bool)e.namedItem("v").toElement().text().toInt();
                                                        emit searchItem(info);
                                                        n = n.nextSibling();
                                                }
                                        }
                                        else if (node.toElement().attribute("id", "") == "tr")
                                        {
                                                QDomNode n = node.toElement().namedItem("query").toElement().firstChild();
                                                if(!n.isNull())
                                                {
                                                        QDomElement e = n.toElement();
                                                        QTlenUserInfo info;
                                                        info.jid	= username + QString("@tlen.pl");
                                                        info.first	= decode(e.namedItem("first").toElement().text());
                                                        info.last	= decode(e.namedItem("last").toElement().text());
                                                        info.nick	= decode(e.namedItem("nick").toElement().text());
                                                        info.email	= decode(e.namedItem("email").toElement().text());
                                                        info.city	= decode(e.namedItem("c").toElement().text());
                                                        info.school	= decode(e.namedItem("e").toElement().text());
                                                        info.job	= e.namedItem("j").toElement().text().toInt();
                                                        info.lookingFor	= e.namedItem("r").toElement().text().toInt();
                                                        info.sex	= e.namedItem("s").toElement().text().toInt();
                                                        info.year	= e.namedItem("b").toElement().text().toInt();
                                                        info.visible	= (bool)e.namedItem("v").toElement().text().toInt();
                                                        emit myInfoArrived(info);
                                                }
                                        }
                                }
                                else if (node.toElement().attribute("type") == "set")
                                {
                                        //pewnie jakaś aktualizacja rostera
                                        //na pewno znajdziemy tam tag <query>
                                        QDomNode e = node.toElement().namedItem("query").toElement().firstChild();
                                        while(!e.isNull())
                                        {
                                                QString group("");
                                                QString jid = e.toElement().attribute("jid");
                                                QString name = decode(e.toElement().attribute("name"));
                                                QString subs = e.toElement().attribute("subscription");
                                                if(!e.toElement().namedItem("group").isNull())
                                                        group = decode(e.toElement().namedItem("group").toElement().text());
                                                emit rosterItem(jid, group, name, subs);
                                                e = e.nextSibling();
                                        }
                                }
                                else if (node.toElement().attribute("type") == "error" and node.toElement().attribute("id", "") == sessionId)
                                        emit authorizationError();
                        }
                }
                //ktoś wylazł z nory
                else if (node.nodeName() == "presence")
                {
                        QString user = node.toElement().attribute("from", "");
                        if(node.toElement().hasAttribute("type") and node.toElement().attribute("type", "") == "subscribe" and !node.toElement().hasAttribute("ask"))
                        {
                                emit autorizationRequest(user);
                        }
                        else
                        {
                                QString desc("");
                                QString avatar_type("-1");
                                QString avatar_digest("");
                                QTlenPresence type = Offline;
                                if(!node.toElement().namedItem("status").isNull())
                                {
                                        desc = decode(node.toElement().namedItem("status").toElement().text());
                                }
                                //Pobieramy typ avatara
                                if(!node.toElement().namedItem("avatar").isNull())
                                {
                                        avatar_type=node.toElement().namedItem("avatar")
                                                    .toElement().namedItem("a")
                                                    .toElement().attribute("type", "-1");
                                        avatar_digest=node.toElement().namedItem("avatar")
                                                    .toElement().namedItem("a")
                                                    .toElement().attribute("md5", "");
                                }
                                if(node.toElement().hasAttribute("type"))
                                {
                                        if (node.toElement().attribute("type", "") == "unavailable")
                                                type = Offline;
                                }
                                else
                                {
                                        QString plainType = node.toElement().firstChild().toElement().text();
                                        if (plainType == "available")
                                                type = Online;
                                        else if (plainType == "chat")
                                                type = Chatty;
                                        else if (plainType == "away")
                                                type = Away;
                                        else if (plainType == "xa")
                                                type = XA;
                                        else if (plainType == "dnd")
                                                type = DND;
                                }
                                emit presenceFrom(user, type, desc, avatar_type, avatar_digest);
                        }
                }
                node=node.nextSibling();
        }
/*
bool QTlenParser::readInput(QByteArray input)
{
	qDebug("Called QTlenParser::readInput()\n");
	qDebug(input + "\n\n");
	addData(input);
	while (!atEnd())
	{
		readNext();
		if (isStartElement())
		{
			if (name() == "s")
			{
				readSession();
			}
			else if (name() == "m")
				readM();
			else if (name() == "message")
				readMessage();
			else if (name() == "iq")
				readIq();
			else if (name() == "presence")
				readPresence();
			else
				readUnknownElement();
		}
	}
	return !error();
}

void QTlenParser::readUnknownElement()
{
	qDebug("Called QTlenParser::readUnknownElement()\n");
	Q_ASSERT(isStartElement());
	
			qDebug("Document:\n");
			qDebug(name().toString().toAscii());
	while (!atEnd())
	{
		readNext();
		if (isEndElement())
			break;
		if (isStartElement())
			readUnknownElement();
	}
}

void QTlenParser::readSession()
{
	qDebug("Called readSession()\n");
	Q_ASSERT(isStartElement() && name() == "s");
	sessionId = attributes().value("i").toString();
	emit connected();
	while (!atEnd())
	{
		readNext();
		if (isEndElement())
		{
			if(name() == "iq")
				readIq();
			else
				break;
		}
		if (isStartElement())
		{
			if (name() == "m")
				readM();		// DONE
			else if (name() == "message")
				readMessage();		// DONE
			else if (name() == "iq")
				readIq();
			else if (name() == "presence")
				readPresence();
			else
				readUnknownElement();
		}
	}
}

void QTlenParser::readM()
{
	Q_ASSERT(isStartElement() && name() == "m");
	QString tp	= attributes().value("tp").toString();
	QString jid	= attributes().value("f").toString();
	//readElementText - przyda się pewnie, co?
	if (tp == "t")
		emit typingStarted(jid);
	else if (tp == "u")
		emit typingStopped(jid);
	else if (tp == "a")
		emit soundAlert(jid);
}

void QTlenParser::readMessage()
{
	Q_ASSERT(isStartElement() && name() == "message");
	QDateTime datetime	= QDateTime::currentDateTime();
	QString jid		= attributes().value("from").toString();
	QString body("");
	emit typingStopped(jid);
	while (!atEnd())
	{
		readNext();
		if (isEndElement())
			break;
		if (isStartElement())
		{
			if (name() == "body")
				body = readMessageBody();
			else if (name() == "x")
				datetime = readMessageDelay();
			else
				readUnknownElement();
		}
	}
	if (jid != "b73@tlen.pl")
		emit message(jid, body, datetime);
}

QString QTlenParser::readMessageBody()
{
	Q_ASSERT(isStartElement() && name() == "body");
	return decode(readElementText());
}

QDateTime QTlenParser::readMessageDelay()
{
	Q_ASSERT(isStartElement() && name() == "x");
	QDateTime datetime;
	QString stamp = attributes().value("stamp").toString();
	int year = stamp.mid( 0, 4 ).toInt();
	int month = stamp.mid( 4, 2 ).toInt();
	int day = stamp.mid( 6, 2 ).toInt();
	int hour = stamp.mid( 9, 2 ).toInt();
	int min = stamp.mid( 12, 2 ).toInt();
	int sec = stamp.mid( 15, 2 ).toInt();
	datetime.setDate( QDate( year, month, day ) );
	datetime.setTime( QTime( hour, min, sec ) );
	return datetime;
}

void QTlenParser::readIq()
{
	qDebug("Called QTlenParser::readIq()\n");
	Q_ASSERT(isStartElement() && name() == "iq");
	if (attributes().value("from") == "c")
	{
		//czat
	}
	else
	{
		if (attributes().value("id") == "GetRoster")
		{
			emit rosterInfoBegin();
			while (!atEnd())
			{
				readNext();
				if (isEndElement())
					break;
				if (isStartElement())
				{
					if (name() == "query")
						readRosterQuery();
					else
						readUnknownElement();
				}
			}
		}
		else if (attributes().value("type") == "result")
		{
			//dodatkowo dostajemy avatar, ale to tylko oznacza, że jesteśmy zalogowani
			if (attributes().value("id").toString() == sessionId)
			{
				emit authenticated();
			}
			//wizytówka, czyli info o kontakcie
			else if (attributes().value("id") == "src3@abcd")
			{
				while (!atEnd())
				{
					readNext();
					if (isEndElement())
						break;
					if (isStartElement())
					{
						if (name() == "query")
							readVcardQuery();
						else
							readUnknownElement();
					}
				}
			}
			//wyniki wyszukiwania
			else if (attributes().value("id") == "src")
			{
				while (!atEnd())
				{
					readNext();
					if (isEndElement())
						break;
					if (isStartElement())
					{
						if (name() == "query")
							readSearchQuery();
						else
							readUnknownElement();
					}
				}
			}
			//info o nas
			else if (attributes().value("id") == "tr")
			{
				while (!atEnd())
				{
					readNext();
					if (isEndElement())
						break;
					if (isStartElement())
					{
						if (name() == "query")
							readMyInfoQuery();
						else
							readUnknownElement();
					}
				}
			}
		}
		else if (attributes().value("type") == "set")
		{
			while (!atEnd())
			{
				readNext();
				if (isEndElement())
					break;
				if (isStartElement())
				{
					if (name() == "query")
						readRosterUpdateQuery();
					else
						readUnknownElement();
				}
			}
		}
		else if (attributes().value("type") == "error" and attributes().value("id") == sessionId)
			emit authorizationError();
	}
}

void QTlenParser::readRosterQuery()
{
	qDebug("Called QTlenParser::readRosterQuery()\n");
	Q_ASSERT(isStartElement() && name() == "query");
	while (!atEnd())
	{
		readNext();
		if (isEndElement())
			break;
		if (isStartElement())
		{
			if (name() == "item")
				readRosterItem();
			else
				readUnknownElement();
		}
	}
}
void QTlenParser::readRosterItem()
{
	Q_ASSERT(isStartElement() && name() == "item");
	QString jid		= attributes().value("jid").toString();
	QString nick		= decode(attributes().value("name").toString());
	QString subscription	= attributes().value("subscription").toString();
	QString group("Tlen");
	while (!atEnd())
	{
		readNext();
		if (isEndElement())
			break;
		if (isStartElement())
		{
			if (name() == "group")
				group = decode(readElementText());
		}
	}
	emit rosterItem(jid, group, nick, subscription);
}

void QTlenParser::readVcardQuery()
{
	Q_ASSERT(isStartElement() && name() == "query");
	while (!atEnd())
	{
		readNext();
		if (isEndElement())
			break;
		if (isStartElement())
		{
			if (name() == "item")
				readVcardItem();
			else
				readUnknownElement();
		}
	}
}

void QTlenParser::readVcardItem()
{
	Q_ASSERT(isStartElement() && name() == "item");
	QTlenUserInfo info;
	info.jid = attributes().value("jid").toString();
	while (!atEnd())
	{
		readNext();
		if (isEndElement())
			break;
		if (isStartElement())
		{
			if (name() == "first")
				info.first = decode(readElementText());
			else if(name() == "last")
				info.last = decode(readElementText());
			else if(name() == "nick")
				info.nick = decode(readElementText());
			else if(name() == "email")
				info.email = decode(readElementText());
			else if(name() == "c")
				info.city = decode(readElementText());
			else if(name() == "e")
				info.school = decode(readElementText());
			else if(name() == "j")
				info.job = readElementText().toInt();
			else if(name() == "r")
				info.lookingFor = readElementText().toInt();
			else if(name() == "s")
				info.sex = readElementText().toInt();
			else if(name() == "b")
				info.year = readElementText().toInt();
		}
	}
	emit vcardArrived(info);
}

void QTlenParser::readSearchQuery()
{
	Q_ASSERT(isStartElement() && name() == "query");
	while (!atEnd())
	{
		readNext();
		if (isEndElement())
			break;
		if (isStartElement())
		{
			if (name() == "item")
				readSearchItem();
			else
				readUnknownElement();
		}
	}
}
///readSearchItem();

void QTlenParser::readSearchItem()
{
	Q_ASSERT(isStartElement() && name() == "item");
	QTlenUserInfo info;
	info.jid = attributes().value("jid").toString();
	while (!atEnd())
	{
		readNext();
		if (isEndElement())
			break;
		if (isStartElement())
		{
			if (name() == "first")
				info.first = decode(readElementText());
			else if(name() == "last")
				info.last = decode(readElementText());
			else if(name() == "nick")
				info.nick = decode(readElementText());
			else if(name() == "email")
				info.email = decode(readElementText());
			else if(name() == "c")
				info.city = decode(readElementText());
			else if(name() == "e")
				info.school = decode(readElementText());
			else if(name() == "j")
				info.job = readElementText().toInt();
			else if(name() == "r")
				info.lookingFor = readElementText().toInt();
			else if(name() == "s")
				info.sex = readElementText().toInt();
			else if(name() == "b")
				info.year = readElementText().toInt();
			else if(name() == "a")
				info.presence = readElementText().toInt();
		}
	}
	emit searchItem(info);
}
void QTlenParser::readMyInfoQuery()
{
	Q_ASSERT(isStartElement() && name() == "query");
	while (!atEnd())
	{
		readNext();
		if (isEndElement())
			break;
		if (isStartElement())
		{
			if (name() == "item")
				readMyInfoItem();
			else
				readUnknownElement();
		}
	}
}
void QTlenParser::readMyInfoItem()
{
	Q_ASSERT(isStartElement() && name() == "item");
	QTlenUserInfo info;
	//info.jid = username;
	while (!atEnd())
	{
		readNext();
		if (isEndElement())
			break;
		if (isStartElement())
		{
			if (name() == "first")
				info.first = decode(readElementText());
			else if(name() == "last")
				info.last = decode(readElementText());
			else if(name() == "nick")
				info.nick = decode(readElementText());
			else if(name() == "email")
				info.email = decode(readElementText());
			else if(name() == "c")
				info.city = decode(readElementText());
			else if(name() == "e")
				info.school = decode(readElementText());
			else if(name() == "j")
				info.job = readElementText().toInt();
			else if(name() == "r")
				info.lookingFor = readElementText().toInt();
			else if(name() == "s")
				info.sex = readElementText().toInt();
			else if(name() == "b")
				info.year = readElementText().toInt();
			else if(name() == "v")
				info.visible = (bool)readElementText().toInt();
		}
	}
	emit myInfoArrived(info);
}
void QTlenParser::readRosterUpdateQuery()
{
	Q_ASSERT(isStartElement() && name() == "query");
	while (!atEnd())
	{
		readNext();
		if (isEndElement())
			break;
		if (isStartElement())
		{
			if (name() == "item")
				readRosterItem();
			else
				readUnknownElement();
		}
	}
}

///readPresence();
void QTlenParser::readPresence()
{
	Q_ASSERT(isStartElement() && name() == "presence");
	QString jid = attributes().value("from").toString();
	if (attributes().value("type") == "subscribe")
		emit autorizationRequest(jid);
	else
	{
		QString desc("");
		QString plainType = attributes().value("type").toString();
		QTlenPresence type;
		while (!atEnd())
		{
			readNext();
			if (isEndElement())
				break;
			if (isStartElement())
			{
				if (name() == "status")
					desc = decode(readElementText());
				else if (name() == "show")
					plainType = readElementText();
			}
		}
		if (plainType == "available")
			type = Online;
		else if (plainType == "chat")
			type = Chatty;
		else if (plainType == "away")
			type = Away;
		else if (plainType == "xa")
			type = XA;
		else if (plainType == "dnd")
			type = DND;
		else
			type = Offline;
		emit presenceFrom(jid, type, desc);
	}
}

QString QTlenParser::decode(QString string)
{
	return QString::fromLocal8Bit(urldecode((const char *)string.toAscii().constData()));
};*/
//Funkcje skradzione z innych bibliotek
/* This file is taken from tleex */
/*
 * Ostatnia aktualizacja:
 *
 * - $Id: auth.c,v 1.19 2002/11/25 18:20:49 mati Exp $
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
                unsigned long H[5];
                unsigned long W[80];
                int lenW;
                unsigned long sizeHi, sizeLo;
} j_SHA_CTX;

static void shaHashBlock (j_SHA_CTX * ctx);

void
shaInit (j_SHA_CTX * ctx)
{
	int i;

	ctx->lenW = 0;
	ctx->sizeHi = ctx->sizeLo = 0;

	/* Initialize H with the magic constants (see FIPS180 for constants)
	 */
	ctx->H[0] = 0x67452301L;
	ctx->H[1] = 0xefcdab89L;
	ctx->H[2] = 0x98badcfeL;
	ctx->H[3] = 0x10325476L;
	ctx->H[4] = 0xc3d2e1f0L;

	for (i = 0; i < 80; i++)
		ctx->W[i] = 0;
}


void
shaUpdate (j_SHA_CTX * ctx, unsigned char *dataIn, int len)
{
	int i;

	/* Read the data into W and process blocks as they get full
	 */
	for (i = 0; i < len; i++)
	{
		ctx->W[ctx->lenW / 4] <<= 8;
		ctx->W[ctx->lenW / 4] |= (unsigned long) dataIn[i];
		if ((++ctx->lenW) % 64 == 0)
		{
			shaHashBlock (ctx);
			ctx->lenW = 0;
		}
		ctx->sizeLo += 8;
		ctx->sizeHi += (ctx->sizeLo < 8);
	}
}


void
shaFinal (j_SHA_CTX * ctx, unsigned char hashout[20])
{
	unsigned char pad0x80 = 0x80;
	unsigned char pad0x00 = 0x00;
	unsigned char padlen[8];
	int i;

	/* Pad with a binary 1 (e.g. 0x80), then zeroes, then length
	 */
	padlen[0] = (unsigned char) ((ctx->sizeHi >> 24) & 255);
	padlen[1] = (unsigned char) ((ctx->sizeHi >> 16) & 255);
	padlen[2] = (unsigned char) ((ctx->sizeHi >> 8) & 255);
	padlen[3] = (unsigned char) ((ctx->sizeHi >> 0) & 255);
	padlen[4] = (unsigned char) ((ctx->sizeLo >> 24) & 255);
	padlen[5] = (unsigned char) ((ctx->sizeLo >> 16) & 255);
	padlen[6] = (unsigned char) ((ctx->sizeLo >> 8) & 255);
	padlen[7] = (unsigned char) ((ctx->sizeLo >> 0) & 255);
	shaUpdate (ctx, &pad0x80, 1);
	while (ctx->lenW != 56)
		shaUpdate (ctx, &pad0x00, 1);
	shaUpdate (ctx, padlen, 8);

	/* Output hash
	 */
	for (i = 0; i < 20; i++)
	{
		hashout[i] = (unsigned char) (ctx->H[i / 4] >> 24);
		ctx->H[i / 4] <<= 8;
	}

	/*
	 *  Re-initialize the context (also zeroizes contents)
	 */
	shaInit (ctx);
}


void
shaBlock (unsigned char *dataIn, int len, unsigned char hashout[20])
{
	j_SHA_CTX ctx;

	shaInit (&ctx);
	shaUpdate (&ctx, dataIn, len);
	shaFinal (&ctx, hashout);
}


#define SHA_ROTL(X,n) ((((X) << (n)) | ((X) >> (32-(n)))) & 0xffffffffL)

static void
shaHashBlock (j_SHA_CTX * ctx)
{
	int t;
	unsigned long A, B, C, D, E, TEMP;

	for (t = 16; t <= 79; t++)
		ctx->W[t] =
			SHA_ROTL (ctx->W[t - 3] ^ ctx->W[t - 8] ^ ctx->
				  W[t - 14] ^ ctx->W[t - 16], 1);

	A = ctx->H[0];
	B = ctx->H[1];
	C = ctx->H[2];
	D = ctx->H[3];
	E = ctx->H[4];

	for (t = 0; t <= 19; t++)
	{
		TEMP = (SHA_ROTL (A, 5) + (((C ^ D) & B) ^ D) + E +
			ctx->W[t] + 0x5a827999L) & 0xffffffffL;
		E = D;
		D = C;
		C = SHA_ROTL (B, 30);
		B = A;
		A = TEMP;
	}
	for (t = 20; t <= 39; t++)
	{
		TEMP = (SHA_ROTL (A, 5) + (B ^ C ^ D) + E + ctx->W[t] +
			0x6ed9eba1L) & 0xffffffffL;
		E = D;
		D = C;
		C = SHA_ROTL (B, 30);
		B = A;
		A = TEMP;
	}
	for (t = 40; t <= 59; t++)
	{
		TEMP = (SHA_ROTL (A, 5) + ((B & C) | (D & (B | C))) + E +
			ctx->W[t] + 0x8f1bbcdcL) & 0xffffffffL;
		E = D;
		D = C;
		C = SHA_ROTL (B, 30);
		B = A;
		A = TEMP;
	}
	for (t = 60; t <= 79; t++)
	{
		TEMP = (SHA_ROTL (A, 5) + (B ^ C ^ D) + E + ctx->W[t] +
			0xca62c1d6L) & 0xffffffffL;
		E = D;
		D = C;
		C = SHA_ROTL (B, 30);
		B = A;
		A = TEMP;
	}

	ctx->H[0] += A;
	ctx->H[1] += B;
	ctx->H[2] += C;
	ctx->H[3] += D;
	ctx->H[4] += E;
}

char *
shahash (char *str)
{
	static char final[41];
	char *pos;
	unsigned char hashval[20];
	int x;

	if (!str || strlen (str) == 0)
		return NULL;

	shaBlock ((unsigned char *) str, strlen (str), hashval);

	pos = final;
	for (x = 0; x < 20; x++)
	{
		snprintf (pos, 3, "%02x", hashval[x]);
		pos += 2;
	}
	return (char *) final;
}

void
shahash_r (const char *str, char hashbuf[41])
{
	int x;
	char *pos;
	unsigned char hashval[20];

	if (!str || strlen (str) == 0)
		return;

	shaBlock ((unsigned char *) str, strlen (str), hashval);

	pos = hashbuf;
	for (x = 0; x < 20; x++)
	{
		snprintf (pos, 3, "%02x", hashval[x]);
		pos += 2;
	}

	return;
}


int calc_passcode(const char* pass, char* code) {
    int magic1 = 0x50305735;
    int magic2 = 0x12345671;
    int sum = 7;
    char z;
    while ((z = *pass++) != 0) {
        if (z == ' ') continue;
        if (z == '\t') continue;
        magic1 ^= (((magic1 & 0x3f) + sum) * z) + (magic1 << 8);
        magic2 += (magic2 << 8) ^ magic1;
        sum += z;
    }
    magic1 &= 0x7fffffff;
    magic2 &= 0x7fffffff;
    return sprintf(code, "%08x%08x", magic1, magic2);
} // end _calc_passcode();

char *tlen_hash (const char *pass, const char *id)
{
	char passcode[17];
	char dohasha[25];
	char *hash;
	hash = (char *) malloc (41);
	calc_passcode (pass, passcode);
	strcpy (dohasha, id);
	strcat (dohasha, passcode);
        dohasha[24]=0;
	shahash_r (dohasha, hash);
	return (char *) hash;
}

/* Following two functions are from OpenBSD's ftp command.  Check:
 * http://www.openbsd.org/cgi-bin/cvsweb/src/usr.bin/ftp/fetch.c?rev=1.55&content-type=text/x-cvsweb-markup
 * for more information.
 *
 * Copyright (c) 1997 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Jason Thorpe and Luke Mewburn.
 * [...]
 */
char
hextochar(const char *str)
{
	char c, ret;

	c = str[0];
	ret = c;
	if (isalpha(c))
		ret -= isupper(c) ? 'A' - 10 : 'a' - 10;
	else
		ret -= '0';
	ret *= 16;

	c = str[1];
	ret += c;
	if (isalpha(c))
		ret -= isupper(c) ? 'A' - 10 : 'a' - 10;
	else
		ret -= '0';
	return ret;
}

char *
urldecode(const char *str)
{
	char *ret, c;
	int i, reallen;

	if (str == NULL) {
		return NULL;
	}
	if ((ret = (char *)malloc(strlen(str)+1)) == NULL) return NULL;
	for (i = 0, reallen = 0; str[i] != '\0'; i++, reallen++, ret++) {
		c = str[i];
		if (c == '+') {
			*ret = ' ';
			continue;
		}
		/* Can't use strtol here because next char after %xx may be
		 * a digit. */
		if (c == '%' && isxdigit(str[i+1]) && isxdigit(str[i+2])) {
			*ret = hextochar(&str[i+1]);
			i+=2;
			continue;
		}
		*ret = c;
	}
	*ret = '\0';

	return ret-reallen;
}

/* Stolen from libtlen sources */
char *
urlencode(const char *msg)
{
	unsigned char *s;
	unsigned char *str;
	unsigned char *pos;

	str = (unsigned char *) calloc(1, 3 * strlen(msg) + 1);
	if (str == NULL ) 
		return NULL;

	s = (unsigned char *)msg;
	pos = str;

	while (*s != '\0') {
		if (*s == ' ') {
			*pos = '+';
			pos++;
		} else if ((*s < '0' && *s != '-' && *s != '.')
			|| (*s < 'A' && *s > '9')
			|| (*s > 'Z' && *s < 'a' && *s != '_')
			|| (*s > 'z')) {
			    sprintf((char *)pos, "%%%02X", *s);
			    pos += 3;
		} else {
			*pos = *s;
			pos++;
		}

		s++;
	}

	return (char *)str;
}
