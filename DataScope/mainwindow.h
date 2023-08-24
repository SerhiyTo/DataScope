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
#include <QPlainTextEdit>
#include <QToolBar>

#include "db_worker.h"

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

private:
    DB_worker db_worker;

    QMenuBar *menuBar;
    QMenu *menuOpen;
    QMenu *menuConnections;
    QMenu *menuTools;
    QMenu *menuSqlite;

    QAction *actionSumbit;
    QAction *actionBack;

    QWidget *centralWidget;
    QVBoxLayout *v_layout;
    QHBoxLayout *h_layout;

    QPlainTextEdit *txtRequest;
    QToolBar *toolWithDB;
    QTableView *tableViewer;
    QListWidget *listWithTables;

    QString fileSqlPath;
};
#endif // MAINWINDOW_H
