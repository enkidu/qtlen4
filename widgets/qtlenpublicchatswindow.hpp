#ifndef QTLENPUBLICCHATSWINDOW_HPP
#define QTLENPUBLICCHATSWINDOW_HPP
#include "qtlenpublicchatwidget.h"
#include <QtGui>
class QTlenPublicChatsWindow : public QWidget
{
Q_OBJECT
public:
    QTlenPublicChatsWindow(QWidget * parent = 0, Qt::WFlags f = 0 );
    QTreeWidget* mainPage;
    QTabWidget *tabWidget;
public slots:
    void openPublicChats(QString);
    void spawnChat(QTlenPublicChatWidget*, QString);
signals:
    void chatRoomRequest(QString, QString);
protected:
    void closeEvent(QCloseEvent*);
};

#endif // QTLENPUBLICCHATSWINDOW_HPP

