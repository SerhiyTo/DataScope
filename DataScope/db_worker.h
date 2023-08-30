#ifndef DB_WORKER_H
#define DB_WORKER_H

#include <QObject>
#include <QDebug>

#include <QtSql>
#include <QSqlQuery>
#include <QTableView>
#include <QSqlQueryModel>
#include <QSqlTableModel>

#include <QMessageBox>

class DB_worker : public QObject
{
    Q_OBJECT
public:
    explicit DB_worker(QObject *parent = nullptr);
    ~DB_worker();

public:
    void connectToDB(const QString& driverName, const QString hostName, const int port, const QString user,
                     const QString password, const QString dbName);
    void connectToDB(const QString& driverName, const QString path);
    void disconnectFromDB();
    QVector<QString> getTables();
    QSqlTableModel* showData(const QString& tableName);
    void sumbit();
    void reject();
    void deleteRow(int index);
    void addRow();
    QSqlRecord record(int index);
    int getRowsCount() const;
    int getColumnsCount() const;

private:
    QSqlDatabase database;
    QTableView* view;
    QSqlTableModel* model;

signals:

};

#endif // DB_WORKER_H
