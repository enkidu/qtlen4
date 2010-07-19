#ifndef HISTORYMANAGER_HPP
#define HISTORYMANAGER_HPP
#include <QtCore>
#include <QtSql/QtSql>
#include "defines.h"
#include <QThread>

class QTlenHistoryManager : public QThread
{
    Q_OBJECT
    public:
        QTlenHistoryManager(QObject * parent = 0);
	~QTlenHistoryManager(){db.close();}
        void getMessages(QString);
 signals:
        void lastMessages(QString, const QList<QTlenMessageStruct>&);
    public slots:
        //jid, body, stamp
        void getLastMessages(QString, int);
        void saveMessage(const QString&, const QString&, const QString&, const QDateTime&);
    private:
	QSqlDatabase db;
    protected:
        void run();
};

#endif // HISTORYMANAGER_HPP
