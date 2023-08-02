#ifndef DB_WORKER_H
#define DB_WORKER_H

#include <QObject>
#include <QDebug>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

class DB_worker : public QObject
{
    Q_OBJECT
public:
    explicit DB_worker(QObject *parent = nullptr);
    ~DB_worker();

private:
    QSqlDatabase database;

public:
    void setDriverDB(const QString& driverName);

    void connectToDB(const QString hostName, const int port, const QString user,
                     const QString password, const QString dbName);

    void connectToDB(const QString path);

signals:

};

#endif // DB_WORKER_H
