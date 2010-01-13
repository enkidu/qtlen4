#include "textdocument.hpp"

TextDocument::TextDocument()
{
}

QString TextDocument::toHtml()
{
    QString html;
    html += header;
    foreach(Message msg, messages)
    {
        html += body.replace("{%nick}", msg.nick)
                .replace("{%date}", msg.date)
                .replace("{%time}", msg.time)
                .replace("{%body}", msg.body);
    }
    html += footer;
    return html;
}

void TextDocument::appendMessage(QDateTime dateTime,
                   QString nick,
                   QString body)
{
    Message msg;
    msg.body = body;
    msg.nick = nick;
    msg.date = dateTime.toString("dd.MM.YY");
    msg.time = dateTime.toString("hh:mm:ss");
    messages.append(msg);
}

void TextDocument::clear()
{
    messages.clear();
}

void TextDocument::insertImage(QString name, QString nick)
{
    Message msg;
    msg.body = "<img src=\"" + name +"\" />";
    msg.nick = nick;
    msg.date = QDate::currentDate().toString("dd.MM.ss");
    msg.time = QTime::currentTime().toString("hh:mm:ss");
}
