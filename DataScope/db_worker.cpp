#include "db_worker.h"

DB_worker::DB_worker(QObject *parent)
    : QObject(parent)
{
    view = new QTableView;
}

DB_worker::~DB_worker()
{

}

void DB_worker::connectToDB(const QString& driverName, const QString hostName, const int port, const QString user,
                            const QString password, const QString dbName)
{
    database = QSqlDatabase::addDatabase(driverName);
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

void DB_worker::connectToDB(const QString& driverName, const QString path)
{
    database = QSqlDatabase::addDatabase(driverName);
    database.setDatabaseName(path);
    if (!database.open())
    {
        qDebug() << "Cannot open database: " << database.lastError();
    }
}

QVector<QString> DB_worker::getTables()
{
    QVector<QString> listWithTables;  // Crete variable for store all tables' names
    foreach(QString item, database.tables())
    {
        listWithTables.append(item);
    }
    return listWithTables;
}

QSqlTableModel* DB_worker::showData(const QString& tableName)
{
    model = new QSqlTableModel(view);  // Create new QSqlTableModel
    model->setTable(tableName);  // Set the table to model
    model->select();
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    return model;
}

void DB_worker::sumbit()
{
    model->submitAll();
}

void DB_worker::reject()
{
    model->revertAll();
}

void DB_worker::deleteRow(int index)
{
    model->removeRow(index);
}

void DB_worker::addRow()
{
    model->insertRow(model->rowCount(QModelIndex()));
}

QSqlRecord DB_worker::record(int index)
{
    return model->record(index);
}

int DB_worker::getRowsCount() const
{
    return model->rowCount();
}

int DB_worker::getColumnsCount() const
{
    return model->columnCount();
}

void DB_worker::disconnectFromDB()
{
    if (database.isOpen())
    {
        database.close();
    }
}
