#ifndef QTLENCRYPTEDSOCKET_H
#define QTLENCRYPTEDSOCKET_H

#include <QObject>
#include <QtNetwork/QtNetwork>
#include <openssl/aes.h>
class QTlenCryptedSocket : public QObject
{
Q_OBJECT
public:
    QTlenCryptedSocket();
    QByteArray readAll();
private:
    QTcpSocket                      *socket;
    bool                            crypted;
    unsigned char                   *clientIv;
    unsigned char                   *serverIv;
    QByteArray                      AESEncrypt(QByteArray);
    QByteArray                      AESDecrypt(QByteArray);
    unsigned char                   *aesKey;
    QByteArray                      prebuffer;
public slots:
    void write(QByteArray);
    void switchCrypted(bool);
    void setCryptInfo(QString e, QString pq, QString iv);
    void connectToHost(QString host, quint16 port);
    void disconnectFromHost();
signals:
    void readyRead();
};

#endif // QTLENCRYPTEDSOCKET_H
