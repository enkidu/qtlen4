#ifndef HISTORYMANAGER_HPP
#define HISTORYMANAGER_HPP
#include <QtCore>
#include <QtSql>
#include "defines.h"
class QTlenHistoryManager : public QObject
{
    Q_OBJECT
    public:
	QTlenHistoryManager();
	~QTlenHistoryManager(){db.close();}
	QList<QTlenMessageStruct> getLastMessages(QString, int);
	QList<QTlenMessageStruct> getMessages(QString);
    public slots:
	//jid, body, stamp
	void saveMessage(QString, QString, QString, QDateTime);
    private:
	QSqlDatabase db;
};

#endif // HISTORYMANAGER_HPP
