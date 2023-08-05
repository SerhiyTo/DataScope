#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMenuBar>
#include <QMenu>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QPushButton>
#include <QVBoxLayout>

#include "db_worker.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openSqlite();
    void openSql();

private:
    DB_worker db_worker;

    QMenuBar *menuBar;
    QMenu *menuOpen;
    QMenu *menuConnections;
    QMenu *menuTools;
    QMenu *menuSqlite;

    QTreeWidget *treeWidget;

    QString fileSqlPath;
};
#endif // MAINWINDOW_H
