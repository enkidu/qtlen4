#include "qtlencryptedsocket.h"
#include <openssl/crypto.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <openssl/bn.h>
#include <openssl/rsa.h>
#include <iostream>
#include <fstream>
QTlenCryptedSocket::QTlenCryptedSocket()
{
    socket      = new QTcpSocket;
    crypted     = false;
    connect(socket,
            SIGNAL(readyRead()),
            this,
            SIGNAL(readyRead()));
}

void QTlenCryptedSocket::connectToHost(QString host, quint16 port)
{
    socket->connectToHost(host, port);
}

void QTlenCryptedSocket::setCryptInfo(QString be, QString pq, QString iv)
{
    QByteArray ba_be, ba_pq, ba_iv;

    //server initialisation vector
    ba_iv = QByteArray::fromHex(iv.toAscii());
    char* c_iv = new char[ba_iv.size()];
    strcpy(c_iv, ba_iv.data());
    serverIv = (unsigned char*)c_iv;
    //RSA n & e
    CRYPTO_malloc_debug_init();
    CRYPTO_dbg_set_options(V_CRYPTO_MDEBUG_ALL);
    CRYPTO_mem_ctrl(CRYPTO_MEM_CHECK_ON);

    RSA *RSAkey = RSA_new();
    ba_be = QByteArray::fromHex(be.size() %2 ? be.prepend("0").toAscii() : be.toAscii());
    ba_pq = QByteArray::fromHex(pq.toAscii());
    RSAkey->n = BN_bin2bn((const unsigned char*)ba_pq.data(),
                          ba_pq.size(),
                          RSAkey->n);
    RSAkey->e = BN_bin2bn((const unsigned char*)ba_be.data(),
                          ba_be.size(),
                          RSAkey->e);
    //key generation
    aesKey = new unsigned char[16];
    //maybe strange but needed
    do {} while(!RAND_bytes(aesKey, 16));
    unsigned char *ptext_ex = (unsigned char*)malloc(64);
    for (int i = 0; i < 48; i++)
        *(ptext_ex+i) = 0;
    memcpy(ptext_ex+48,aesKey,16);
    clientIv = new unsigned char[16];
    do {} while(!RAND_bytes(clientIv, 16));

    unsigned char ctext[256];
    //64 - lenght of ptext_ex
    RSA_public_encrypt(64, ptext_ex, ctext, RSAkey, RSA_NO_PADDING);
    QByteArray hash = QByteArray((const char*)ctext, 64).toHex();
    QByteArray ivHash = QByteArray((const char *)clientIv,16).toHex();
    write("<cipher k1='"+ hash +"' k2='"+ ivHash +"'/>");
}

void QTlenCryptedSocket::write(QByteArray data)
{
    QByteArray u;
    if (!crypted)
    {
        u = data;
        qDebug() << "\033[0;40;36m"<< "unencrypted" <<"\033[0m";
    }
    else
    {
        u = AESEncrypt(data);

    }
    qDebug() << "\033[0;40;32m<< " << data << "\033[0m";
    socket->write(u);
    qDebug() << "\033[0;40;36m<< " << socket->errorString() <<"\033[0m";
}

void QTlenCryptedSocket::disconnectFromHost()
{
    socket->disconnectFromHost();
    crypted=false;
}

QByteArray QTlenCryptedSocket::readAll()
{
    QByteArray data = socket->readAll();
    if (!crypted)
    {
        return data;
    }
    else
    {
        QByteArray u = AESDecrypt(data);
        return u;
    }

}

void QTlenCryptedSocket::switchCrypted(bool yesno)
{
    crypted = yesno;
}

QByteArray QTlenCryptedSocket::AESEncrypt(QByteArray data)
{
        //dopełniamy rozmiar bloku
        while ((data.length() % 16) != 0)
            data.append(" ");
        QByteArray output("");
        while (data.size() > 0)
        {
            QByteArray tmp = data.left(1024);
            int size = tmp.size();
            unsigned char *outbuf = new unsigned char[1024];
            memset(outbuf, 0, sizeof(outbuf));
            AES_KEY aeskey;
            AES_set_encrypt_key(aesKey, 16*8, &aeskey);
            AES_cbc_encrypt((const unsigned char*)tmp.data(), outbuf, size, &aeskey, clientIv, AES_ENCRYPT);
            data.remove(0, 1024);
            output.append((const char *)outbuf, size);
        }
        return output;
}

QByteArray QTlenCryptedSocket::AESDecrypt(QByteArray data)
{
        QByteArray output("");
        data.prepend(prebuffer);
        prebuffer.clear();
        int chop = data.size() % 16;
        prebuffer = data.right(chop);
        data.remove(data.size() - chop, chop);
        while (data.size() > 0)
        {
            QByteArray tmp = data.left(1024);
            int size = tmp.size();
            unsigned char *outbuf = new unsigned char[1024];
            memset(outbuf, 0, sizeof(outbuf));
            AES_KEY aeskey;
            AES_set_decrypt_key(aesKey, 16*8, &aeskey);
            AES_cbc_encrypt((const unsigned char*)tmp.data(), outbuf, size, &aeskey, serverIv, AES_DECRYPT);
            data.remove(0, 1024);
            output.append((const char *)outbuf, size);
        }
        return output;
}
