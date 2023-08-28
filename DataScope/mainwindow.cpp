#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    txtRequest = new QPlainTextEdit(this);
    txtRequest->setMaximumHeight(250);

    v_layout = new QVBoxLayout;
    h_layout = new QHBoxLayout;

    tableViewer = new QTableView(this);
    listWithTables = new QListWidget(this);

    toolWithDB = new QToolBar(this);
    toolWithDB->setMovable(false);

    toolWithRequest = new QToolBar(this);
    toolWithRequest->setMovable(false);

    menuBar = new QMenuBar(this);
    menuOpen = new QMenu("Open", this);
    menuConnections = new QMenu("Connections", this);
    menuTools = new QMenu("Tools", this);

    QAction *openSqlite = new QAction (tr("&SQLite"), this);
    connect(openSqlite, &QAction::triggered, this, &MainWindow::openSqlite);

    actionSumbit = new QAction(tr("&Submit") ,this);
    actionBack = new QAction(tr("&Reject"), this);
    actionRun = new QAction(tr("&Run"), this);

    model = new QSqlQueryModel(this);

    connect(actionSumbit, &QAction::triggered, this, &MainWindow::sumbitRequest);
    connect(actionBack, &QAction::triggered, this, &MainWindow::rejectRequest);
    connect(actionRun, &QAction::triggered, this, &MainWindow::playSqlQuery);

    actionSumbit->setIcon(QIcon(":/iconOK.png"));
    actionBack->setIcon(QIcon(":/iconNo.png"));
    actionRun->setIcon(QIcon(":/iconPlay.png"));

    actionSumbit->setEnabled(false);
    actionBack->setEnabled(false);
    actionRun->setEnabled(false);

    toolWithDB->addAction(actionSumbit);
    toolWithDB->addAction(actionBack);
    toolWithRequest->addAction(actionRun);

    menuBar->addMenu(menuOpen);
    menuBar->addMenu(menuConnections);
    menuBar->addMenu(menuTools);

    menuConnections->addAction(openSqlite);

    this->setMenuBar(menuBar);

    v_layout->addWidget(toolWithRequest);
    v_layout->addWidget(txtRequest);
    v_layout->addWidget(toolWithDB);
    v_layout->addWidget(tableViewer);

    listWithTables->setMaximumWidth(250);

    h_layout->addWidget(listWithTables);
    h_layout->addLayout(v_layout);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(h_layout);
    setCentralWidget(centralWidget);

    connect(listWithTables, &QListWidget::itemClicked, this, &MainWindow::openCurrentTable);
    connect(tableViewer, &QTableView::doubleClicked, this, &MainWindow::changeIcons);
    connect(txtRequest, &QPlainTextEdit::textChanged, this, &MainWindow::changeEnabledPlay);
}

MainWindow::~MainWindow()
{
    delete txtRequest;
    delete v_layout;
    delete h_layout;
    delete tableViewer;
    delete listWithTables;
    delete toolWithDB;
    delete toolWithRequest;
    delete menuBar;
    delete menuOpen;
    delete menuConnections;
    delete menuTools;
    delete actionSumbit;
    delete actionBack;
    delete actionRun;
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
    tableViewer->setSortingEnabled(true);
    tableViewer->show();
}

void MainWindow::sumbitRequest()
{
    db_worker.sumbit();
    actionSumbit->setEnabled(false);
    actionBack->setEnabled(false);
}

void MainWindow::rejectRequest()
{
    db_worker.reject();
    actionSumbit->setEnabled(false);
    actionBack->setEnabled(false);
}

void MainWindow::changeIcons()
{
    actionSumbit->setEnabled(true);
    actionBack->setEnabled(true);
}

void MainWindow::playSqlQuery()
{
    model->setQuery(txtRequest->toPlainText());
    if (model->lastError().isValid())
    {
        QMessageBox::critical(this,
                              "Error",
                              model->lastError().text());
    }
    tableViewer->setModel(model);
    tableViewer->show();
}

void MainWindow::changeEnabledPlay()
{
    actionRun->setEnabled(!txtRequest->toPlainText().isEmpty());
}

void MainWindow::openSqlite()
{
    fileSqlPath = QFileDialog::getOpenFileName(this, "Open", QString(), "All files(*.*);;DB (*.db)");
    if (fileSqlPath.isEmpty()) return;
    db_worker.connectToDB("QSQLITE", fileSqlPath);
    showTables();
}

