#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include <QVector>
#include "PingObject.h"
#include "PingTask.h"
#include <QTreeWidgetItem>
#include <qprocess.h>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    GUItimer = new QTimer();
    GUItimer->start(500);
    QObject::connect(GUItimer,SIGNAL(timeout()),SLOT(update_listview()));

    tasktimer = new QTimer();
    tasktimer->start(500);
    QObject::connect(tasktimer,SIGNAL(timeout()),SLOT(timerExpired()));
    QThreadPool::globalInstance()->setMaxThreadCount(20);

    QObject::connect(ui->actionOpen,SIGNAL(triggered()),SLOT(load_hostfiledialog()));
    QObject::connect(ui->actionQuit,SIGNAL(triggered()),SLOT(close()));

}

void MainWindow::timerExpired()
{
    QDateTime next;
    QDateTime current;
    PingObject * oldest;

    if (pinglist.size() > 0 & !ui->actionPause->isChecked()) {
        for (int i=0; i< pinglist.size(); i++) {
             next = pinglist.at(i)->get_nextpingtime();
             current = QDateTime().currentDateTime();
                 if ((next < current) & ((pinglist.at(i)->get_threadstatus() =="finished") | (pinglist.at(i)->get_threadstatus() =="begin"))  ) {

                 PingTask * pingtask = new PingTask();
                 pingtask->pingobject = pinglist.at(i);
                 QThreadPool::globalInstance()->tryStart(pingtask);
             }
         }
    }
}

bool MainWindow::load_hostfile(QString filename)
{
    PingObject * pingInstance;
    int counter=0;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return 1;

    QTextStream in(&file);
    QString line = "";
    while (!line.isNull()) {

       line = in.readLine();
       if ((line[0] != '#') & (line.length() > 0)) {
           pingInstance = new PingObject();
           pingInstance->set_host(line);
           pingInstance->set_id(counter);
           pingInstance->set_nextpingtime(QDateTime().currentDateTime());
           counter++;
           pinglist.append(pingInstance);
       }
    }
    init_listview();

    return true;
}

void MainWindow::init_listview() {
    QTreeWidgetItem * item;
    for (int i=0 ; i < pinglist.size(); i ++) {

        item = new QTreeWidgetItem(pinglist.at(i)->get_data());
        ui->treeWidget->addTopLevelItem(item);
    }
    for (int i=0 ; i < ui->treeWidget->columnCount(); i ++) {
        ui->treeWidget->resizeColumnToContents(i);
    }
}

void MainWindow::update_listview() {
    QTreeWidgetItem * item;
    QColor background;
    QColor text;

    for (int i=0 ; i < pinglist.size(); i ++) {

        item = ui->treeWidget->topLevelItem(i);
        item->setText(0,pinglist.at(i)->get_host());
        item->setText(1,QString().setNum(pinglist.at(i)->get_pingssent()));
        item->setText(2,QString().setNum(pinglist.at(i)->get_avgRTT(),'f',1) + " ms");
        item->setText(3,QString().setNum(pinglist.at(i)->get_curRTT(),'f',1) + " ms");
        item->setText(4,pinglist.at(i)->get_progress());
        item->setText(5,pinglist.at(i)->get_threadstatus());
        if (pinglist.at(i)->get_threadstatus() != "begin" & pinglist.at(i)->get_curRTT()<0.1) {
            background=Qt::red; text = Qt::white;
        }
        else {
            background=Qt::white; text = Qt::black;
        }
        for (int i=0 ; i < ui->treeWidget->columnCount(); i++) {
            item->setBackgroundColor(i,background);
            item->setTextColor(i,text);
        }
    }
    for (int i=0 ; i < ui->treeWidget->columnCount(); i ++) {
        ui->treeWidget->resizeColumnToContents(i);
    }
}

void MainWindow::load_hostfiledialog() {
   QFileDialog * filedialog;
   filedialog = new QFileDialog(this);
   filedialog->show();
   QObject::connect(filedialog, SIGNAL(fileSelected(QString)),SLOT(load_hostfile(QString)));

}

MainWindow::~MainWindow() {
    delete ui;
}
