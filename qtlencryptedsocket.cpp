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
    //te dane niestety wkompilujemy na stałe (na razie)
    static unsigned char siv[] = "\x71\x77\x65\x72\x74\x79\x75\x69\x61\x73\x64\x66\x67\x68\x6a\x6b";
    serverIv = siv;
    static unsigned char n[] =
        "\x15\x54\xa7\x87\x3b\x24\xbb\x3e\x0c\x01\x01\x67\x5e\x01\x8f\xe1"
        "\x84\xfa\x3c\x9e\x66\xe8\x0a\x4c\x33\xb6\xf2\x55\x2e\x7e\x9c\x2b"
        "\x67\x18\x65\xe1\xb5\x6c\xe1\x70\x18\x04\xc5\x50\xcf\x12\x4a\x86"
        "\x14\xb2\x5e\x1f\x66\xc1\xc5\x8a\x62\x9f\x7b\xe9\x4b\x36\x50\xfd";

    static unsigned char e[] = "\x01\x00\x01";

    RSA *RSAkey;
    unsigned char ctext[256];
    unsigned char * key = random(16);
    static unsigned char ptext_ex[] =
            "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
            "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
            "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
            "\xc7\x3b\x79\xe1\x72\xd2\x2b\xa4\xd8\xd0\xde\xc8\xf8\x0b\x9c\x7c";
    int i = 0;
    for (int i = 0; i < 48; i++)
    {
        ptext_ex[i] = 0;
    }
    for (int i = 48; i < 64; i++)
    {
        ptext_ex[i] = key[i-48];
    }
    static unsigned char ptext_exx[]= "\xc7\x3b\x79\xe1\x72\xd2\x2b\xa4\xd8\xd0\xde\xc8\xf8\x0b\x9c\x7c";
    unsigned char * tiv = random(16);
    for (int i = 0; i < 16; i++)
    {
        ptext_exx[i] = tiv[i];
    }
    aesKey = key;
    clientIv = ptext_exx;

    int plen;

    CRYPTO_malloc_debug_init();
    CRYPTO_dbg_set_options(V_CRYPTO_MDEBUG_ALL);
    CRYPTO_mem_ctrl(CRYPTO_MEM_CHECK_ON);

    plen = sizeof(ptext_ex) - 1;

    RSAkey = RSA_new();
    RSAkey->n = BN_bin2bn(n, sizeof(n)-1, RSAkey->n);
    RSAkey->e = BN_bin2bn(e, sizeof(e)-1, RSAkey->e);
    RSAkey->d = NULL;
    RSAkey->p = NULL;
    RSAkey->q = NULL;
    RSAkey->dmp1 = NULL;
    RSAkey->dmq1 = NULL;
    RSAkey->iqmp = NULL;
    RSA_public_encrypt(plen, ptext_ex, ctext, RSAkey, RSA_NO_PADDING);
    QByteArray hash = QCA::arrayToHex(QByteArray((const char*)ctext, 64)).toAscii();
    QByteArray ivHash = QCA::arrayToHex(QByteArray((const char *)clientIv)).toAscii();
    socket->write("<cipher k1='"+ hash +"' k2='"+ ivHash +"'/>");
}

void QTlenCryptedSocket::write(QByteArray data)
{
    QByteArray u;
    if (!crypted)
        u = data;
    else
    {
        u = AESEncrypt(data);

    }
    socket->write(u);
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

unsigned char * QTlenCryptedSocket::random(int size)
{
        char * buffer;
        char * byte;
        int i;
        std::ifstream is;
        is.open("/dev/random", std::ios::binary);
        buffer = new char [size];
        byte = new char [1];
        i = 0;
        while (i < size)
        {
            is.read(byte, 1);
            if (byte != 0)
            {
                buffer[i] = byte[0];
                i++;
            }
        }
        is.close();
        return (unsigned char *)buffer;
}
