#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMenuBar>
#include <QMenu>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTableView>
#include <QListWidget>
#include <QTextEdit>
#include <QToolBar>
#include <QSqlQueryModel>
#include <QSortFilterProxyModel>
#include <QJsonObject>

#include "db_worker.h"
#include "syntaxhighlighter.h"

static const QMap<QString, QString> map_databases = {
    {"&MySql", "QMYSQL"},
    {"&PostgreSql", "QPSQL"},
    {"&Microsoft SQL Server", "QODBC"}
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void showTables();

private slots:
    void openSqlite();
    void openSql();
    void openCurrentTable();
    void sumbitRequest();
    void rejectRequest();
    void changeIcons();
    void playSqlQuery();
    void changeEnabledPlay();
    void addRecord();
    void deleteRecord();
    void saveDataToJson();

private:
    DB_worker db_worker;

    QMenuBar *menuBar;
    QMenu *menuOpen;
    QMenu *menuConnections;
    QMenu *menuTools;
    QMenu *menuSqlite;

    QSqlQueryModel *model;

    QAction *actionSumbit;
    QAction *actionBack;
    QAction *actionRun;
    QAction *actionAddRecord;
    QAction *actionDeleteRecord;
    QAction *actionSaveInJson;

    QWidget *centralWidget;
    QVBoxLayout *v_layout;
    QHBoxLayout *h_layout;

    QTextEdit *txtRequest;
    QSyntaxHighlighter *m_Highligter;

    QToolBar *toolWithDB;
    QToolBar *toolWithRequest;
    QTableView *tableViewer;
    QListWidget *listWithTables;

    QString fileSqlPath;
};
#endif // MAINWINDOW_H
