#ifndef DB_WORKER_H
#define DB_WORKER_H

#include <QObject>
#include <QDebug>

#include <QtSql/QSqlDatabase>

class DB_worker : public QObject
{
    Q_OBJECT
public:
    explicit DB_worker(QObject *parent = nullptr);
    ~DB_worker();

private:
    QSqlDatabase database;  // <=== Error here

public:
    void connectToDB(const QString hostName, const QString port, const QString user,
                     const QString password, const QString dbName);

    void connectToDB(const QString path);


    void setDatabase(const QSqlDatabase &newDatabase);

signals:

};

#endif // DB_WORKER_H
