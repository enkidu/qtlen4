#ifndef QTLENPUBLICCHATSMANAGER_HPP
#define QTLENPUBLICCHATSMANAGER_HPP

#include <QObject>
#include "chatroomnode.h"
#include <QtGui>
#include <QTreeWidget>
#include "qtlenpublicchatwidget.h"
#include "qtlenpublicchatswindow.hpp"
#include "qtlenchatwindow.hpp"
class ChatItem
{
public:
    ChatItem(){id = ""; widget = 0;}
    ~ChatItem(){}
    ChatItem(const ChatItem &other)
    {
        id = other.id;
        widget = other.widget;
    }
    QString id;
    QTlenPublicChatWidget* widget;
};
class PrivItem
{
public:
    PrivItem(){id = ""; widget = 0;}
    ~PrivItem(){}
    PrivItem(const PrivItem &other)
    {
        id = other.id;
        widget = other.widget;
    }
    QString id;
    QTlenChatWidget* widget;
};

class QTlenPublicChatsManager : public QObject
{
Q_OBJECT
public:
    QTlenPublicChatsManager(QObject * parent = 0);
    QList<ChatRoomNode> roomList;
    QTlenPublicChatsWindow* window;
    QList<ChatItem> activeChats;
    QList<PrivItem> activePrivs;
    void showWindow();
public slots:
    void appendList(QString, QList<ChatRoomNode>);
    void handleDoubleClick(QTreeWidgetItem*, int);
    void presence(QString, QString, int, bool);
    void message(QString, QString, QString, QString);
    void closePage(int);
    void openPriv(QString);
private:
    QTreeWidgetItem* findItem(QString) const;
    ChatRoomNode findNodeByItem(QTreeWidgetItem*) const;
    ChatItem findItemById(QString) const;
    QString findIdByItem(QTlenPublicChatWidget*) const;
    int findIndexOfChat(QTlenPublicChatWidget*) const;
    int findIndexOfPriv(QTlenChatWidget*) const;
    PrivItem findPrivById(QString) const;
    bool isOpenChat(QString id) const;
    bool isOpenPriv(QString id) const;
signals:
    void expandNode(QString);
    void getTopLevel();
    void openPublicChat(QString);
    void spawnChat(QTlenPublicChatWidget*, QString);
    void leaveChatroom(QString);
    void message(QString, QString);
    void privMessage(QString, QString);
};

#endif // QTLENPUBLICCHATSMANAGER_HPP
