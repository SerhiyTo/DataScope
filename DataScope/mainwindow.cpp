#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    db_worker.setDatabase(QSqlDatabase::addDatabase("QPSQL"));
}

MainWindow::~MainWindow()
{
}

