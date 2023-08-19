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

    showTables();
    showData();

    database.close();
}

void DB_worker::showTables()
{
    qInfo() << "showTables:";
    QStringList lst = database.tables();
    foreach(QString str, lst)
    {
        qDebug() << "Table: " << str;
    }
}

void DB_worker::showData()
{
//    QSqlTableModel model;
//    model.setTable(QString(database.tables().last()));
//    model.select();
//    // model.setEditStrategy(QSqlTableModel::OnFieldChange);
//    view.setModel(&model);
//    view.show();
    auto* model = new QSqlTableModel(view);
    model->setTable(QString(database.tables().last()));
    model->select();
    view->setModel(model);
    view->show();
}
