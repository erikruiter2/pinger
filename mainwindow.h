#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "PingObject.h"
#include "PingTask.h"
#include <QProcess>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);


    void init_listview();


    QVector<PingObject *> pinglist;
    QVector<PingTask *> pingtasks;

    QTimer * tasktimer;
    QTimer * GUItimer;
    ~MainWindow();

public slots:
    bool load_hostfile(QString filename);
    void load_hostfiledialog();
    void update_listview();
    void timerExpired();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
