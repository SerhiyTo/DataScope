#include "db_worker.h"

DB_worker::DB_worker(QObject *parent)
    : QObject(parent)
{

}

DB_worker::~DB_worker()
{

}

void DB_worker::setDatabase(const QSqlDatabase &newDatabase)
{
//    database = newDatabase;
}

void DB_worker::connectToDB(const QString hostName, const QString port, const QString user,
                            const QString password, const QString dbName)
{
    if (database.driverName() != nullptr)
    {
        qInfo() << database.driverName();
    }
}

void DB_worker::connectToDB(const QString path)
{

}
