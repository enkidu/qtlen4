#include "avatarsmanager.hpp"

QTlenAvatarsManager::QTlenAvatarsManager()
{
    db= QSqlDatabase::addDatabase("QSQLITE", "avatars");
    db.setDatabaseName(QDir::homePath().append("/.qtlen4/avatars.sq3"));
    db.open();
    if (db.tables().isEmpty())
    {
        QSqlQuery query(db);
        query.exec("CREATE TABLE avatars (id INTEGER PRIMARY KEY, jid, digest, pixmap)");
    }
    path = QDir::homePath().append("/.qtlen4/avatars/");
    dir = QDir();
}

QPixmap QTlenAvatarsManager::getAvatar(QString nick, QString digest)
{
    QSqlQuery query(db);
    query.prepare("SELECT pixmap FROM avatars WHERE (jid = :jid) AND (digest = :digest)");
    query.bindValue(":jid", nick);
    query.bindValue(":digest", digest);
    query.setForwardOnly(true);
    query.exec();
    if (query.next())
    {
        qDebug("fetching av from db");
        QByteArray ba = query.value(0).toByteArray();
        QPixmap pix;
        pix.loadFromData(ba);
        return pix;
    }
    return QPixmap::QPixmap();
}

void QTlenAvatarsManager::saveAvatar(QString nick, QString digest, QPixmap avatar)
{
    QByteArray ba;
    QBuffer buf(&ba);
    buf.open(QIODevice::WriteOnly);
    avatar.save(&buf, "PNG");
    QSqlQuery query(db);
    query.prepare("SELECT id FROM avatars WHERE (jid = :jid) AND (digest = :digest)");
    query.bindValue(":jid", nick);
    query.bindValue(":digest", digest);
    query.exec();
    if (query.next())
    {
        int id = query.value(0).toInt();
        QSqlQuery update(db);
        update.prepare("UPDATE avatars pixmap = :pixmap WHERE id = :id");
        update.bindValue(":id", id);
        update.bindValue(":pixmap", ba);
        update.exec();
    }
    else
    {
        QSqlQuery insert(db);
        insert.prepare("INSERT INTO avatars(jid, digest, pixmap)"
                       "VALUES(:jid, :digest, :pixmap)");
        insert.bindValue(":jid", nick);
        insert.bindValue(":digest", digest);
        insert.bindValue(":pixmap", ba);
        insert.exec();
    }
}

QTlenAvatarsFetcher::QTlenAvatarsFetcher()
{
}

QPixmap QTlenAvatarsFetcher::getAvatar(QTlenAvatarsManager* manager,
				       QTlenMailConfig config,
				       QString token,
				       QString nick,
				       QString digest)
{
    this->manager = manager;
    this->nick = nick;
    this->digest = digest;
    QPixmap pixmap = manager->getAvatar(nick, digest);
    http = new QHttp();
    if (!pixmap.isNull())
	return pixmap;
    else
    {
        qDebug("fetching from server");
	QString request = "/" + config.avatarGetUrl
			  .replace("^login^", nick)
			  .replace("^token^", token)
			  .replace("^type^", "0");
	QUrl url = QUrl(config.baseUrl);
	connect(http, SIGNAL(done(bool)), this, SLOT(setFinished(bool)));
	http->setHost(url.host());
	http->get (request.toAscii());
    }
	return QPixmap(QString::fromUtf8(":/icons/icons/64x64/default_av.png"));

}

void QTlenAvatarsFetcher::setFinished(bool error)
{
    qDebug("finished");
    if(!error)
    {
	QPixmap raw = QPixmap();
	QByteArray data = http->readAll();
	if (raw.loadFromData(data))
	{
            qDebug("got avatar");
	    emit gotAvatar(nick + "@tlen.pl", raw);
	    manager->saveAvatar(nick, digest, raw);
	}
    }
}

void QTlenAvatarSaver::saveAvatar(QTlenMailConfig config, QByteArray data, QString token, int access)
{
    http = new QHttp();
    //<avatar-upload method='POST'>taved/?cmd=save%26t=^token^%26access=^access^%26type=^type^</avatar-upload>
    QString request = "/" + config.avatarSetUrl
		      .replace("^token^", token)
		      .replace("^access^", "0")
		      .replace("^type^", "0");
    QUrl url = QUrl(config.baseUrl);
    QHttpRequestHeader header("POST", QUrl::fromPercentEncoding(request.toAscii()));
    header.setValue("Host", url.host());
    header.setValue("Content-Type", "multipart/form-data; boundary=AaB03x");
    data.prepend("--AaB03x\r\nContent-Disposition: form-data; name=\"filename\"; filename=\"plik.png\"\r\nContent-Type: image/png\r\n\r\n");
    data.append("\r\n--AaB03x--\r\n");
    connect(http,
	    SIGNAL(done(bool)),
	    this,
	    SLOT(result()));
    http -> setHost(url.host());
    http -> request(header, data);
}

void QTlenAvatarSaver::result()
{
    QByteArray result = http->readAll();
    if (result.startsWith("<ok"))
	emit saved();
    else
	emit error();
    exit();
}
