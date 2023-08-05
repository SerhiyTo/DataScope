#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // db_worker.setDriverDB("QPSQL");
    // db_worker.connectToDB("localhost", 5432, "postgres", "w55w7y4t#$", "postgres");
//    db_worker.setDriverDB("QSQLITE");
//    db_worker.connectToDB("Path");

    menuBar = new QMenuBar(this);
    menuOpen = new QMenu("Open", this);
    menuConnections = new QMenu("Connections", this);
    menuTools = new QMenu("Tools", this);

    QAction *openSqlite = new QAction (tr("&SQLite"), this);
    connect(openSqlite, &QAction::triggered, this, &MainWindow::openSqlite);

    menuBar->addMenu(menuOpen);
    menuBar->addMenu(menuConnections);
    menuBar->addMenu(menuTools);

    menuConnections->addAction(openSqlite);

    this->setCentralWidget(menuBar);

    treeWidget = new QTreeWidget(this);
}

MainWindow::~MainWindow()
{
}

void MainWindow::openSql()
{
    fileSqlPath = QFileDialog::getOpenFileName(this, "Open", QString(), "All files(*.*);;SQL (*.sql)");
    qInfo() << fileSqlPath;
    if (fileSqlPath.isEmpty()) return;
}

void MainWindow::openSqlite()
{
    fileSqlPath = QFileDialog::getOpenFileName(this, "Open", QString(), "All files(*.*);;DB (*.db)");
    qInfo() << fileSqlPath;
    if (fileSqlPath.isEmpty()) return;
}

