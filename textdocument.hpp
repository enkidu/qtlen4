#ifndef TEXTDOCUMENT_HPP
#define TEXTDOCUMENT_HPP
#include <QtCore>

class TextDocument
{
public:
    struct Message
    {
        QString date;
        QString time;
        QString nick;
        QString body;
    };
    TextDocument();
    QString toHtml();
    void insertImage(QString, QString);
    void appendMessage(QDateTime, QString, QString);
    void clear();
private:
    QList<Message> messages;
    QString header;
    QString footer;
    QString body;
};

#endif // TEXTDOCUMENT_HPP
