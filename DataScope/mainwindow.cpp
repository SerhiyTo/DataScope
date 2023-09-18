#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    txtRequest = new QTextEdit(this);  // Create QTextEdit for input the SQL query
    txtRequest->setMaximumHeight(200);  // Set minimum height for our QTextEdit
    QFont font = txtRequest->font();  // Get font
    font.setPointSize(12);  // Set font size
    txtRequest->setFont(font);  // update font
    m_Highligter = new SyntaxHighlighter(txtRequest->document());  // include syntax highligter
    connect(txtRequest, &QTextEdit::textChanged, this, &MainWindow::changeEnabledPlay);  // Connect function for change status
                                                                                         // button, when text were changed

    v_layout = new QVBoxLayout;  // Create new vertical box layout
    h_layout = new QHBoxLayout;  // Create new horizontal box layout

    tableViewer = new QTableView(this);  // Create new table for output data from database
    connect(tableViewer, &QTableView::doubleClicked, this, &MainWindow::changeIcons);  // Connect function for change status,
                                                                                       // when would be mouse double click

    listWithTables = new QListWidget(this);  // Create new QListWidget for output tables in our database
    listWithTables->setMaximumWidth(250);  // Set maximum width for this widget
    connect(listWithTables, &QListWidget::itemClicked, this, &MainWindow::openCurrentTable);  // Connect function for open
                                                                                              // current table, that was selected

    toolWithDB = new QToolBar(this);  // Create new QToolBar with actions: submit, reject changed in tables, ...
    toolWithDB->setMovable(false);  // Block movable

    toolWithRequest = new QToolBar(this);  // Create new QToolBar with actions: run our sql query, ...
    toolWithRequest->setMovable(false);  // Block movable

    menuBar = new QMenuBar(this);  // Create new QMenuBar with actions: connect to database, open file with query, tools...
    this->setMenuBar(menuBar);  // Set menu bar for our application

    menuOpen = new QMenu("Open", this);  // Create new QMenu for open file with query
    menuConnections = new QMenu("Connections", this);  // Create new QMenu for connect with our database
    menuTools = new QMenu("Tools", this);  // Create new QMenu for tools

    QAction *openSqlite = new QAction (tr("&SQLite"), this);  // Create action for connect to sqlite
    connect(openSqlite, &QAction::triggered, this, &MainWindow::openSqlite);  // Open function for connect to sqlite,
                                                                              // when button was clicked


    actionSumbit = new QAction(tr("&Submit") ,this);  // Create new action for Submit changes in table
    actionBack = new QAction(tr("&Reject"), this);  // Create new action for Cancel changes in tab;e
    actionRun = new QAction(tr("&Run"), this);  // Create neww action for run SQL-query
    actionAddRecord = new QAction(tr("&Add"), this);
    actionDeleteRecord = new QAction(tr("&Delete"), this);
    actionSaveInJson = new QAction(tr("&Save"), this);

    // Set hints for our actions
    actionSumbit->setToolTip("Commit table changes");
    actionBack->setToolTip("Cancel table changes");
    actionRun->setToolTip("Run SQL-query");
    actionAddRecord->setToolTip("Add new record to table");
    actionDeleteRecord->setToolTip("Delete record from table");
    actionSaveInJson->setToolTip("Save data from tables to JSON format");

    // Set icons for our actions
    actionSumbit->setIcon(QIcon(":/iconOK.png"));
    actionBack->setIcon(QIcon(":/iconNo.png"));
    actionRun->setIcon(QIcon(":/iconPlay.png"));
    actionAddRecord->setIcon(QIcon(":/iconAdd.png"));
    actionDeleteRecord->setIcon(QIcon(":/iconDelete.png"));
    actionSaveInJson->setIcon(QIcon(":/iconSave.png"));

    // Set buttons disenabled
    actionSumbit->setEnabled(false);
    actionBack->setEnabled(false);
    actionRun->setEnabled(false);
    actionAddRecord->setEnabled(false);
    actionDeleteRecord->setEnabled(false);
    actionSaveInJson->setEnabled(false);

    // Connect actions' signals with slots
    connect(actionSumbit, &QAction::triggered, this, &MainWindow::sumbitRequest);
    connect(actionBack, &QAction::triggered, this, &MainWindow::rejectRequest);
    connect(actionRun, &QAction::triggered, this, &MainWindow::playSqlQuery);
    connect(actionAddRecord, &QAction::triggered, this, &MainWindow::addRecord);
    connect(actionDeleteRecord, &QAction::triggered, this, &MainWindow::deleteRecord);
    connect(actionSaveInJson, &QAction::triggered, this, &MainWindow::saveDataToJson);

    model = new QSqlQueryModel(this);  // Create model for passing to it data from SQL-query in txtRequest

    // Add actions
    toolWithDB->addAction(actionSumbit);
    toolWithDB->addAction(actionBack);
    toolWithDB->addAction(actionAddRecord);
    toolWithDB->addAction(actionDeleteRecord);
    toolWithDB->addAction(actionSaveInJson);
    toolWithRequest->addAction(actionRun);

    // Add menu to QMenuBar
    menuBar->addMenu(menuOpen);
    menuBar->addMenu(menuConnections);
    menuBar->addMenu(menuTools);

    // Add action to QMenu
    menuConnections->addAction(openSqlite);

    // Add all our widget to vertical box layout
    v_layout->addWidget(toolWithRequest);
    v_layout->addWidget(txtRequest);
    v_layout->addWidget(toolWithDB);
    v_layout->addWidget(tableViewer);

    // Add other widgets to horizontal box layout
    h_layout->addWidget(listWithTables);
    h_layout->addLayout(v_layout);

    QWidget *centralWidget = new QWidget(this);  // Create new centralWidget
    centralWidget->setLayout(h_layout);  // Set our horizontal layout as main layout in this widget
    setCentralWidget(centralWidget);  // Set our centralWidget, as central widget our app
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
    delete actionAddRecord;
    delete actionDeleteRecord;
    delete actionSaveInJson;
}

void MainWindow::showTables()
{
    foreach (const QString& item, db_worker.getTables())
    {
        listWithTables->addItem(item);  // Add every table to our list with table
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
    actionAddRecord->setEnabled(true);
    actionDeleteRecord->setEnabled(true);
    actionSaveInJson->setEnabled(true);

    QString tableName = listWithTables->currentItem()->text();  // Get name of selected item in list widget
    tableViewer->setModel(db_worker.showData(tableName));  // Open table with selected item
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
    tableViewer->setSortingEnabled(true);
    tableViewer->show();
}

void MainWindow::changeEnabledPlay()
{
    // Set our action run enabled if our txtRequest is not empty and tables in our listWithTables more than 0
    actionRun->setEnabled(!txtRequest->toPlainText().isEmpty() && listWithTables->count() > 0);
}

void MainWindow::addRecord()
{
    db_worker.addRow();
    changeIcons();
}

void MainWindow::deleteRecord()
{
    QModelIndexList selectedItem = tableViewer->selectionModel()->selectedIndexes();
    if (selectedItem.isEmpty())
    {
        QMessageBox::critical(this,
                              "Error",
                              "You didn't selected any row!");
        return;
    }
    QModelIndex index = selectedItem.at(0);
    db_worker.deleteRow(index.row());
    changeIcons();
}

void MainWindow::saveDataToJson()
{
    QFile file(QString(listWithTables->currentItem()->text()) + ".json");
    file.open(QIODevice::WriteOnly);
    QJsonArray jsonArray;

    for (int nRow = 0; nRow < db_worker.getRowsCount(); ++nRow)
    {
        QSqlRecord rec = db_worker.record(nRow);
        QJsonObject recordObj;
        for (int nCol = 0; nCol < db_worker.getColumnsCount(); ++nCol)
        {
            recordObj.insert(rec.fieldName(nCol), QJsonValue::fromVariant(rec.value(nCol)));
        }
        jsonArray.append(recordObj);
    }

    file.write(QJsonDocument(jsonArray).toJson());
    file.close();
}

void MainWindow::openSqlite()
{
    fileSqlPath = QFileDialog::getOpenFileName(this, "Open", QString(), "All files(*.*);;DB (*.db)");
    if (fileSqlPath.isEmpty()) return;
    db_worker.connectToDB("QSQLITE", fileSqlPath);
    showTables();
}

