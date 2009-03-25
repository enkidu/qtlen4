#ifndef QTLENPUBLICCHATSMANAGER_HPP
#define QTLENPUBLICCHATSMANAGER_HPP

#include <QObject>

class QTlenPublicChatsManager : public QObject
{
public:
    QTlenPublicChatsManager();
    struct RoomListItem
    {
	int id;
	int parent;
	QString name;
	int flags;
    };
};

#endif // QTLENPUBLICCHATSMANAGER_HPP
