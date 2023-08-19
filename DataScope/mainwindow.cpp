#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // db_worker.setDriverDB("QPSQL");
    // db_worker.connectToDB("localhost", 5432, "postgres", "w55w7y4t#$", "postgres");
    //db_worker.setDriverDB("QSQLITE");
//    db_worker.connectToDB("Path");

    menuBar = new QMenuBar(this);
    menuOpen = new QMenu("Open", this);
    menuConnections = new QMenu("Connections", this);
    menuTools = new QMenu("Tools", this);

    QAction *openSqlite = new QAction (tr("&SQLite"), this);
    connect(openSqlite, &QAction::triggered, this, &MainWindow::openSqlite);
    QAction *openMySql = new QAction (tr("&MySql"), this);
    connect(openMySql, &QAction::triggered, this, &MainWindow::openSql);
//    QAction *openPostg = new QAction (tr("&PostgreSql"), this);
//    connect(openPostg, &QAction::triggered, this, &MainWindow::openSql);
//    QAction *openQODBC = new QAction (tr("&Microsoft SQL Server"), this);
//    connect(openQODBC, &QAction::triggered, this, &MainWindow::openSql);

    menuBar->addMenu(menuOpen);
    menuBar->addMenu(menuConnections);
    menuBar->addMenu(menuTools);

    menuConnections->addAction(openSqlite);
    menuConnections->addAction(openMySql);
//    menuConnections->addAction(openPostg);
//    menuConnections->addAction(openQODBC);

    this->setCentralWidget(menuBar);
    treeWidget = new QTreeWidget(this);
}

MainWindow::~MainWindow()
{
}

void MainWindow::openSql()
{
    QAction* action = qobject_cast<QAction*>(sender());
    fileSqlPath = QFileDialog::getOpenFileName(this, "Open", QString(), "All files(*.*);;SQL (*.sql)");
    qInfo() << fileSqlPath;
    if (fileSqlPath.isEmpty()) return;
    qInfo() << map_databases.value(action->text());
    db_worker.connectToDB(map_databases.value(action->text()), fileSqlPath);
}

void MainWindow::openSqlite()
{
    fileSqlPath = QFileDialog::getOpenFileName(this, "Open", QString(), "All files(*.*);;DB (*.db)");
    qInfo() << fileSqlPath;
    if (fileSqlPath.isEmpty()) return;
    db_worker.connectToDB("QSQLITE", fileSqlPath);
}

