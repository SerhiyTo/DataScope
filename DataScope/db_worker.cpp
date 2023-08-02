#include "db_worker.h"

DB_worker::DB_worker(QObject *parent)
    : QObject(parent)
{

}

DB_worker::~DB_worker()
{

}

void DB_worker::setDriverDB(const QString &driverName)
{
    database = QSqlDatabase::addDatabase(driverName);
}

void DB_worker::setDatabase(const QSqlDatabase &newDatabase)
{
    database = newDatabase;
}

void DB_worker::connectToDB(const QString hostName, const int port, const QString user,
                            const QString password, const QString dbName)
{
    database.setHostName(hostName);
    database.setPort(port);
    database.setUserName(user);
    database.setPassword(password);
    database.setDatabaseName(dbName);

    if (!database.open())
    {
        qInfo() << "Error connection to DB!";
    }
    else
    {
        qInfo() << "Succecfully!";
    }
}

void DB_worker::connectToDB(const QString path)
{
    database.setDatabaseName(path);

    if (!database.open())
    {
        qInfo() << "Error connection to DB!";
    }
}
