#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // db_worker.setDatabase(QSqlDatabase::addDatabase("QPSQL"));
    db_worker.setDriverDB("QPSQL");
    db_worker.connectToDB("localhost", 5432, "postgres", "w55w7y4t#$", "postgres");
}

MainWindow::~MainWindow()
{
}

