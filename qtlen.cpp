#include "qtlen.h"
#include <QtCrypto>
QTlen::QTlen():QObject()
{
	http = new QHttp;
        socket = new QTlenCryptedSocket;
        isConnected = false;
        pingTimer = new QTimer(this);
        pingTimer->setInterval(55000);
	//parser = new QTlenParser;
	connect(http,	SIGNAL(done(bool)),				this,	SLOT(readServerInfo()));
	connect(this,	SIGNAL(serverConnect()),			this,	SLOT(openConnection()));
	connect(socket,	SIGNAL(readyRead()),				this,	SLOT(checkResponse()));
        connect(this,	SIGNAL(connected()),				pingTimer,	SLOT(start()));
	//connect(parser,	SIGNAL(connected()),				this,	SLOT(writeLoginString()));
	connect(this,	SIGNAL(authenticated()),			this,	SLOT(getMailInfo()));
	connect(this,
		SIGNAL(readyToGetRoster()),
		SLOT(getRoster()));
	connect(this,	SIGNAL(parse(QByteArray)),			this,	SLOT(parseResponse(QByteArray)));
	connect(socket,	SIGNAL(error(QAbstractSocket::SocketError)), 	this,	SLOT(displayError(QAbstractSocket::SocketError)));
	connect(this,	SIGNAL(startConnection()),			this,	SLOT(makeConnection()));

        connect(pingTimer,
                SIGNAL(timeout()),
                this,
                SLOT(pinguj()));
}

bool QTlen::is_connected()
{
    return isConnected;
}

void QTlen::setUserParams(QString user, QString pass)
{
	username = user;
	password = pass;
}

void QTlen::makeConnection()
{
	emit connecting();
	QHttpRequestHeader header("GET", "/4starters.php?u=brylozketrzyn&v=91&m=1");
	header.setValue("Host", "idi.tlen.pl");
	header.setValue("User-Agent", "Mozilla/3.0 (compatible)");
	http -> setHost("idi.tlen.pl");
	http -> request(header);
}

void QTlen::readServerInfo()
{
	QByteArray xmlSource=http->readAll();
	QDomDocument doc("");
	doc.setContent(xmlSource);
	QDomElement t = doc.documentElement();
	server=t.attribute("s","");
	QString str_port=t.attribute("p","");
	port = str_port.toUInt();
	remote = t.attribute("r","");
	emit serverConnect();
}

void QTlen::openConnection()
{
	socket->connectToHost(server,port);
        socket->write("<s s=\"1\" v=\"9\" t=\"06000224\">");
}

void QTlen::checkResponse()
{
        QByteArray tmp = socket->readAll();
        //qDebug(tmp);
        cache.append(tmp);
        QDomDocument doc("");
        if(doc.setContent("<package>"+cache+"</package>") or cache.startsWith("<s") or cache.startsWith("<cipher"))
        //if (cache.endsWith(">"))
	{
		emit (parse(cache));
		cache = QByteArray("");
	}
	//parser->readInput(socket->readAll());
}

void QTlen::writeLoginString()
{
	//QByteArray loginString("<iq type=\"set\" id=\""+parser->sessionId.toAscii()+"\"><query xmlns=\"jabber:iq:auth\"><username>"+username.toAscii()+"</username><digest>"+tlenHash(password, parser->sessionId)+"</digest><resource>QTlen4</resource><host>tlen.pl</host></query></iq>");
	//socket->write(loginString);
	//isConnected = true;
}

void QTlen::parseResponse(QByteArray input)
{
	//debug, żeby sobie poczytać, o czym gada z nami serwer
	emit receivedXml(input);

	//profilaktycznie puszczamy pinga
        //socket->write("  \t  ");
	QDomDocument doc("");
	//brzydka sztuczka, konieczna do poradzenia sobie z nawałem śmiecia w jednym pakiecie
	doc.setContent("<package>"+input+"</package>");
	QDomElement root = doc.documentElement();
	QDomNode node = root.firstChild();
	while (!node.isNull())
	{
		if (node.nodeName() == "s") 
		{
			sessionId=node.toElement().attribute("i","");
                        if (node.toElement().attribute("k1","") == "")
                        {
                            emit connected();
                            QByteArray loginString("<iq type=\"set\" id=\""+sessionId.toAscii()+"\"><query xmlns=\"jabber:iq:auth\"><username>"+username.toAscii()+"</username><digest>"+tlenHash(password, sessionId)+"</digest><resource>QTlen4</resource><host>tlen.pl</host></query></iq>");
                            socket->write(loginString);
                        }
                        else
                        {
                            QString k1 = node.toElement().attribute("k1","");
                            QString k2 = node.toElement().attribute("k2","");
                            QString k3 = node.toElement().attribute("k3","");
                            socket->setCryptInfo(k1, k2, k3);
                            //socket->switchCrypted(true);
                            //socket->write("<cipher type='ok'/>");
                            //emit connected();
                            //QByteArray loginString("<iq type=\"set\" id=\""+sessionId.toAscii()+"\"><query xmlns=\"jabber:iq:auth\"><username>"+username.toAscii()+"</username><digest>"+tlenHash(password, sessionId)+"</digest><resource>t</resource><host>tlen.pl</host></query></iq>");
                            //socket->write(loginString);
                        }

		}
                else if (node.nodeName() == "cipher")
                {
                            socket->switchCrypted(true);
                            socket->write("<cipher type='ok'/>");
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
/*
	<m f='261@c/~Pretorius'><b n='6' f='0' c='000000' s='10'>witaj+:D</b></m>

	n - font style (?)
	f - font family
	c - font color
	s - font size
	<b>msg body</b>

	if <m> contains tp='p', it's a private message
*/
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
                        QString type = node.toElement().attribute("type", "");
                        if (type == "pic")
                        {
                            QString idt = node.toElement().attribute("idt", "").toAscii();
                            QString crc = node.toElement().attribute("crc", "");
                            QString rt = node.toElement().attribute("rt", "");
                            if ((crc != "") && (rt == "") && (crc != "n"))
                            {
                                socket->write("<message type='pic' crc_c='n' idt='"+idt.toAscii()+"' to='"+sender.toAscii()+"' />");
                            }
                            else if ((crc == "") && (rt != ""))
                            {
                                emit imageReadyToDownload(rt, idt, sender);
                            }
                            else if (crc == "n")
                            {
                                emit sendImage(idt, sender);
                            }
                        }
                        else
                        //begin wiadomość tekstowa
                        {
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
                        //end wiadomość tekstowa
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
                else if (node.nodeName() == "n")
                {
                    QString sender = decode(node.toElement().attribute("f", ""));
                    QString subject = decode(node.toElement().attribute("s", ""));
                    QString id = node.toElement().attribute("id", "");
                    QString fld = node.toElement().attribute("fld", "");
                }
		node=node.nextSibling();
	}
}

void QTlen::parseMailConfig(QDomNode node)
{
        QDomNode item = node.toElement().firstChild();
        while(!item.isNull())
        {
                if (item.nodeName() == "base")
                    mailConfig.baseUrl = item.toElement().text();
                else if (item.nodeName() == "index")
                {
                    mailConfig.msgUrl       = item.toElement().text();
                    mailConfig.msgMethod    = item.toElement().attribute("method", "GET");
                }
                else if(item.nodeName() == "index")
                {
                    mailConfig.msgIndexUrl      = item.toElement().text();
                    mailConfig.msgIndexMethod   = item.toElement().attribute("method", "GET");
                }
                else if(item.nodeName() == "login")
                {
                    mailConfig.loginUrl         = item.toElement().text();
                    mailConfig.loginMethod      = item.toElement().attribute("method", "POST");
                }
                else if(item.nodeName() == "logout")
                {
                    mailConfig.logoutUrl        = item.toElement().text();
                    mailConfig.logoutMethod     = item.toElement().attribute("method", "GET");
                }
                else if(item.nodeName() == "avatar-get")
                {
                    mailConfig.avatarGetUrl     = item.toElement().text();
                    mailConfig.avatarGetMethod  = item.toElement().attribute("method", "GET");
                }
		else if(item.nodeName() == "avatar-upload")
		{
		    mailConfig.avatarSetUrl     = item.toElement().text();
		    mailConfig.avatarSetMethod  = item.toElement().attribute("method", "GET");
		}
                item=item.nextSibling();
        }
        emit receivedMailConfig(mailConfig);
	emit readyToGetRoster();
           // <logout method='GET'>logout.php</logout>
            //<compose method='GET'>?cmd=compose%26to=^to^</compose>
            //<avatar-get method='GET'>avatar/^login^/^type^?t=^token^</avatar-get>
            //<avatar-upload method='POST'>taved/?cmd=save%26t=^token^%26access=^access^%26type=^type^</avatar-upload>
            //<avatar-remove method='GET'>taved/?cmd=delete%26t=^token^%26type=^type^</avatar-remove>
}

void QTlen::setSubscribed(QString jid, bool yesNo)
{
	if (yesNo)
	{
		socket->write("<presence to=\"" + jid.toAscii() + "\" type=\"subscribed\"/>");
		//dodatowo prosimy o subskrypcję
		socket->write("<presence to=\"" + jid.toAscii() + "\" type=\"subscribe\"/>");
	}
	else
		socket->write("<presence to=\"" + jid.toAscii() + "\" type=\"unsubscribed\"/>");
};

void QTlen::saveRosterItem(QString jid, QString name, QString group)
{
	//TODO:	takie pierdoły napisać w oparciu o DOM
	if (group != "Tlen")
	socket->write("<iq type=\"set\"><query xmlns=\"jabber:iq:roster\"><item jid=\""+jid.toAscii()+"@tlen.pl\" name=\""+encode(name)+"\"><group>"+encode(group)+"</group></item></query></iq>");
	else
	socket->write("<iq type=\"set\"><query xmlns=\"jabber:iq:roster\"><item jid=\""+jid.toAscii()+"@tlen.pl\" name=\""+encode(name)+"\"></item></query></iq>");
};

void QTlen::saveMyInfo(QTlenUserInfo info)
{
	QByteArray packet = QByteArray("<iq type=\"set\" id=\"tw\" to=\"tuba\"><query xmlns=\"jabber:iq:register\">");
	if(!info.first.isNull())
		packet += "<first>" + encode(info.first) + "</first>";
	if(!info.last.isNull())
		packet += "<last>" + encode(info.last) + "</last>";
	if(!info.nick.isNull())
		packet += "<nick>" + encode(info.nick) + "</nick>";
	if(!info.email.isNull())
		packet += "<email>" + encode(info.email) + "</email>";
	if(!info.city.isNull())
		packet += "<c>" + encode(info.city) + "</c>";
	if(!info.school.isNull())
		packet += "<e>" + encode(info.school) + "</e>";
	packet += "<j>" + QByteArray::number(info.job) + "</j>";
	packet += "<s>" + QByteArray::number(info.sex) + "</s>";
	if (info.year != 0)
		packet += "<b>" + QByteArray::number(info.year) + "</b>";
	packet += "<r>" + QByteArray::number(info.lookingFor) + "</r>";
	packet += "<v>" + QByteArray::number((int)info.visible) + "</v>";
	packet += QByteArray("</query></iq>");
	socket->write(packet);
};

void QTlen::writeTyping(QString jid, bool active)
{
    if (active)
	socket->write("<m tp=\"t\" to=\"" + jid.toAscii() + "\"/>");
    else
	socket->write("<m tp=\"u\" to=\"" + jid.toAscii() + "\"/>");
}

void QTlen::searchUsers(QTlenUserInfo info)
{
	QByteArray packet = QByteArray("<iq type=\"get\" id=\"src\" to=\"tuba\"><query xmlns=\"jabber:iq:search\">");
	if(!info.first.isNull())
		packet += "<first>" + encode(info.first) + "</first>";
	if(!info.last.isNull())
		packet += "<last>" + encode(info.last) + "</last>";
	if(!info.nick.isNull())
		packet += "<nick>" + encode(info.nick) + "</nick>";
	if(!info.email.isNull())
		packet += "<email>" + encode(info.email) + "</email>";
	if(!info.city.isNull())
		packet += "<c>" + encode(info.city) + "</c>";
	if(!info.school.isNull())
		packet += "<e>" + encode(info.school) + "</e>";
	packet += "<s>" + QByteArray::number(info.sex) + "</s>";
	packet += "<f>" + QByteArray::number(info.start) + "</f>";
	if(info.visible)
		packet += "<m>2</m>";
	if(info.years_from != 0)
		packet += "<d>" + QByteArray::number(info.years_from) + "</d>";
	if(info.years_to != 0)
		packet += "<u>" + QByteArray::number(info.years_to) + "</u>";
	packet += QByteArray("</query></iq>");
	socket->write(packet);
};

void QTlen::getMailInfo()
{
    socket->write("<iq to='tcfg' type='get' id='" + sessionId.toAscii() +"'></iq>");
}

void QTlen::getRoster()
{

	socket->write("<iq type='get' id='GetRoster'><query xmlns='jabber:iq:roster'></query></iq>");
};

void QTlen::getInfoAboutMyself()
{
	socket->write("<iq type='get' id='tr' to='tuba'><query xmlns='jabber:iq:register'></query></iq>");
};

void QTlen::destroyConnection()
{
	socket->write("</s>");
	socket->disconnectFromHost();
	emit disconnected();
	isConnected = false;
};

QString QTlen::decode(QString string)
{
	return QString::fromLocal8Bit(urldecode((const char *)string.toAscii().constData()));
};

QByteArray QTlen::encode(QString string)
{
	return QByteArray::QByteArray(urlencode((const char *)string.toLocal8Bit().constData()));
};

QByteArray QTlen::tlenHash(QString pass, QString sid)
{
	return QByteArray::QByteArray((const char *)tlen_hash(pass.toAscii().constData(),sid.toAscii().constData()));
};

void QTlen::pinguj()
{
        socket->write("  \t  ");
};

void QTlen::sendMessage(QString address, QString body)
{
	QByteArray message("<message to=\""+address.toAscii()+"\" type=\"chat\"><body>"+encode(body)+"</body></message>");
	socket->write(message);
};

void QTlen::setStatus(int statusCode, QString statusString)
{	
	QByteArray status[] = 
	{
		"available",
		"chatty",
		"away",
		"xa",
		"dnd",
		"invisible",
		"unavailable"
	};
	QByteArray statusNode("");
	if (isConnected)
	{
		if (!statusString.isEmpty())
		{
			statusNode = "<status>" + encode(statusString) + "</status>";
		}
		if (statusCode < 5)
			socket->write("<presence><show>" + status[statusCode] + "</show>" + statusNode + "</presence>");
		else
			socket->write("<presence type=\"" + status[statusCode] +"\">" + statusNode + "</presence>");
		if (statusCode == 6)
		{
			emit disconnected();
			isConnected = false;
		}
	}
	else if (statusCode != 6)
	{
		emit startConnection();
	}
};

void QTlen::getInfoAbout(QString jid)
{
	socket->write("<iq type=\"get\" id=\"src3@abcd\" to=\"tuba\"><query xmlns=\"jabber:iq:search\"><i>"+jid.mid( 0, (jid.length()-8 )).toAscii()+"</i></query></iq>");
};

void QTlen::deleteUser(QString jid)
{
	socket->write("<iq type=\"set\"><query xmlns=\"jabber:iq:roster\"><item jid=\""+jid.toAscii()+"\" subscription=\"remove\"/></query></iq>");
};

void QTlen::sendRawXML(QString xml)
{
	socket->write(xml.toAscii());
};

//Funkcje obsługi tlen-czatów

void QTlen::chatsGetTopLevelGroups()
{
	socket->write("<iq to=\"c\" type=\"1\"/>");
	//socket->write("<iq to='fiza@tlen.pl'><query xmlns='p2p'><fs t=\"fiza@tlen.pl/Tlen\" e=\"1\" i=\"139952408\" c=\"1\" s=\"590\" v=\"2\" /></query></iq>");
};

