#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "db_worker.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    DB_worker db_worker;
};
#endif // MAINWINDOW_H
