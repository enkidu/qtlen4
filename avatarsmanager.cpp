#include "avatarsmanager.hpp"

QTlenAvatarsManager::QTlenAvatarsManager()
{
    path = QDir::homePath().append("/.qtlen4/avatars/");
    dir = QDir();
}

QPixmap QTlenAvatarsManager::getAvatar(QString nick, QString digest)
{
    QString fileName = QString("%1/%2.png").arg(nick, digest);
    return QPixmap::QPixmap (path + fileName);
}

void QTlenAvatarsManager::saveAvatar(QString nick, QString digest, QPixmap avatar)
{
    QString fileName = QString("%1/%2.png").arg(nick, digest);
    if(!dir.exists(path + nick))
	dir.mkpath(path + nick);
    avatar.save(path + fileName);
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
	QString request = "/" + config.avatarGetUrl
			  .replace("^login^", nick)
			  .replace("^token^", token)
			  .replace("^type^", "0");
	qDebug("GET " +request.toAscii());
	QUrl url = QUrl(config.baseUrl);
	connect(http, SIGNAL(done(bool)), this, SLOT(setFinished(bool)));
	http->setHost(url.host());
	http->get (request.toAscii());
    }
	return QPixmap(QString::fromUtf8(":/icons/icons/64x64/default_av.png"));

}

void QTlenAvatarsFetcher::setFinished(bool error)
{
    qDebug("Request Finished");
    if(!error)
    {
	qDebug("OK");
	QPixmap raw = QPixmap();
	QByteArray data = http->readAll();
	if (raw.loadFromData(data))
	{
	    emit gotAvatar(nick + "@tlen.pl", raw);
	    manager->saveAvatar(nick, digest, raw);
	    qDebug("Pixmap saved");
	}
	else
	{
	    qDebug("Wrong pixmap");
	    qDebug(data);
	}
    }
    else
	qDebug(http->errorString().toAscii());
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
