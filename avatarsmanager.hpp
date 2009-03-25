#ifndef AVATARSMANAGER_HPP
#define AVATARSMANAGER_HPP
#include <QtCore>
#include "defines.h"
#include <QtNetwork>
#include <QPixmap>
class QTlenAvatarsManager : public QObject
{
    Q_OBJECT
    public:
        QTlenAvatarsManager();
        ~QTlenAvatarsManager() {}
        QPixmap getAvatar(QString, QString);
        void saveAvatar(QString, QString, QPixmap);
    private:
        QString path;
	QDir dir;
};

class QTlenAvatarsFetcher : public QObject
{
    Q_OBJECT
    public:
	QTlenAvatarsFetcher();
	~QTlenAvatarsFetcher() {}
	QPixmap getAvatar(QTlenAvatarsManager*, QTlenMailConfig, QString, QString, QString);
    private slots:
	void setFinished(bool);
    private:
	QHttp* http;
	QString nick;
	QString digest;
	QTlenAvatarsManager* manager;
    signals:
	void gotAvatar(QString, QPixmap);
};

class QTlenAvatarSaver : public QThread
{
    Q_OBJECT
    public:
	void saveAvatar(QTlenMailConfig, QByteArray, QString, int);
    private:
	QHttp* http;
    private slots:
	void result();
    signals:
	void saved();
	void error();
};

#endif // AVATARSMANAGER_HPP
