#ifndef CHATROOMNODE_H
#define CHATROOMNODE_H
#include <QString>
#include <QtCore>
#include <QTreeWidgetItem>
#include <QtGui>

class ChatRoomNode
{
public:
    ChatRoomNode(){ item = 0;}
    ~ChatRoomNode(){}
    ChatRoomNode(const ChatRoomNode &other)
    {
        id = other.id;
        parent = other.parent;
        name = other.name;
        flags = other.flags;
        item = other.item;
        users = other.users;
    }
    QString id;
    QString parent;
    QString name;
    QTreeWidgetItem* item;
    int users;
    int flags;
};

Q_DECLARE_METATYPE(ChatRoomNode)
#endif // CHATROOMNODE_H
