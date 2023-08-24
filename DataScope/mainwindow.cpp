#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    txtRequest = new QPlainTextEdit(this);
    txtRequest->setMaximumHeight(250);

    v_layout = new QVBoxLayout(this);
    h_layout = new QHBoxLayout(this);

    tableViewer = new QTableView(this);
    listWithTables = new QListWidget(this);

    toolWithDB = new QToolBar(this);
    toolWithDB->setMovable(false);

    menuBar = new QMenuBar(this);
    menuOpen = new QMenu("Open", this);
    menuConnections = new QMenu("Connections", this);
    menuTools = new QMenu("Tools", this);

    QAction *openSqlite = new QAction (tr("&SQLite"), this);
    connect(openSqlite, &QAction::triggered, this, &MainWindow::openSqlite);

    actionSumbit = new QAction(tr("&Submit") ,this);
    actionBack = new QAction(tr("&Reject"), this);
    connect(actionSumbit, &QAction::triggered, this, &MainWindow::sumbitRequest);
    connect(actionBack, &QAction::triggered, this, &MainWindow::rejectRequest);
    actionSumbit->setIcon(QIcon(":/iconOK.png"));
    actionBack->setIcon(QIcon(":/iconNo.png"));
    toolWithDB->addAction(actionSumbit);
    toolWithDB->addAction(actionBack);

    menuBar->addMenu(menuOpen);
    menuBar->addMenu(menuConnections);
    menuBar->addMenu(menuTools);

    menuConnections->addAction(openSqlite);

    this->setMenuBar(menuBar);

    // tableViewer->setMinimumSize(500, 500);

    v_layout->addWidget(txtRequest);
    v_layout->addWidget(toolWithDB);
    v_layout->addWidget(tableViewer);

    listWithTables->setMaximumWidth(250);
    // listWithTables->setMinimumHeight(500);

    // h_layout->addWidget(tableViewer);
    h_layout->addWidget(listWithTables);
    h_layout->addLayout(v_layout);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(h_layout);
    setCentralWidget(centralWidget);

    connect(listWithTables, &QListWidget::itemClicked, this, &MainWindow::openCurrentTable);
}

MainWindow::~MainWindow()
{
}

void MainWindow::showTables()
{
    foreach (const QString& item, db_worker.getTables())
    {
        listWithTables->addItem(item);
    }
}

void MainWindow::openSql()
{
    QAction* action = qobject_cast<QAction*>(sender());
    fileSqlPath = QFileDialog::getOpenFileName(this, "Open", QString(), "All files(*.*);;SQL (*.sql)");
    if (fileSqlPath.isEmpty()) return;
    qInfo() << map_databases.value(action->text());
    db_worker.connectToDB(map_databases.value(action->text()), fileSqlPath);
}

void MainWindow::openCurrentTable()
{
    QString tableName = listWithTables->currentItem()->text();
    tableViewer->setModel(db_worker.showData(tableName));
    tableViewer->resizeColumnsToContents();
    tableViewer->show();
}

void MainWindow::sumbitRequest()
{
    db_worker.sumbit();
}

void MainWindow::rejectRequest()
{
    db_worker.reject();
}

void MainWindow::openSqlite()
{
    fileSqlPath = QFileDialog::getOpenFileName(this, "Open", QString(), "All files(*.*);;DB (*.db)");
    if (fileSqlPath.isEmpty()) return;
    db_worker.connectToDB("QSQLITE", fileSqlPath);
    showTables();
}

