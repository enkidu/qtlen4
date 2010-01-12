#include "historymanager.hpp"

QTlenHistoryManager::QTlenHistoryManager(QObject * parent) : QThread(parent){}

void QTlenHistoryManager::run()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QDir::homePath() + "/.qtlen4/history");
    bool ok = db.open();
    if (db.tables().isEmpty())
    {
	QSqlQuery query;
	query.exec("CREATE TABLE messages (id INTEGER PRIMARY KEY, sent_by, sent_to, body, timestamp)");
	query.exec("CREATE TABLE incoming (id INTEGER PRIMARY KEY, sent_by, sent_to, body, timestamp)");
    }
    exec();
}

void QTlenHistoryManager::saveMessage( const QString &from, const QString &to, const QString &body, const QDateTime &timestamp)
{
    QSqlQuery query;
    query.prepare("INSERT INTO messages (id, sent_by, sent_to, body, timestamp) VALUES (NULL, :sent_by, :sent_to, :body, :timestamp)");
    query.bindValue(":sent_by", from);
    query.bindValue(":sent_to", to);
    query.bindValue(":body", body);
    query.bindValue(":timestamp", timestamp.toTime_t());
    query.exec();

}

void QTlenHistoryManager::getMessages(QString jid)
{
}

void QTlenHistoryManager::getLastMessages(QString jid, int limit)
{
    QList<QTlenMessageStruct> list;
    QSqlQuery query;
    query.prepare("SELECT * FROM messages WHERE ((sent_by = :jid_by) OR (sent_to = :jid_to)) ORDER BY timestamp DESC LIMIT :limit");
    query.bindValue(":jid_by", jid);
    query.bindValue(":jid_to", jid);
    query.bindValue(":limit", limit);
    query.exec();
    int sentByNo = query.record().indexOf("sent_by");
    int sentToNo = query.record().indexOf("sent_to");
    int bodyNo = query.record().indexOf("body");
    int timeNo = query.record().indexOf("timestamp");
    while(query.next())
    {
	QTlenMessageStruct i;
	i.sent_by = query.value(sentByNo).toString();
	i.sent_to = query.value(sentToNo).toString();
	i.body = query.value(bodyNo).toString();
	i.dateTime = QDateTime::fromTime_t(query.value(timeNo).toInt());
	list.append(i);
    }
    emit lastMessages(jid, list);
}
