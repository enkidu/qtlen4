#ifndef QTLENPUBLICCHATWIDGET_H
#define QTLENPUBLICCHATWIDGET_H

#include <QWidget>
#include <QtGui>
#include "qtlentextedit.hpp"
class QTlenPublicChatWidget : public QWidget
{
Q_OBJECT
public:
    QTlenPublicChatWidget(QWidget * parent = 0);
    void appendMessage(QString, QString);
    void presence(QString, int, bool);
    void setRoomId(QString);
private:
    QListWidget *list;
    QTextBrowser *browser;
    QTlenTextEdit *input;
    QString roomId;
private slots:
    void sendMessage();
    void itemDoubleClicked(QListWidgetItem*);
signals:
    void message(QString, QString);
    void startPriv(QString);
};

#endif // QTLENPUBLICCHATWIDGET_H
