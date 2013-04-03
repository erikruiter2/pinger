#include <QThreadPool>
#include "PingObject.h"
#include "PingTask.h"
#include <QProcess>
#include <QDebug>

//PingTask::PingTask() {}

void PingTask::run()
 {
     pingobject->set_threadstatus("run");
     QProcess * process = new QProcess();
     QString command = "/sbin/ping -c 1 -t 3 " + pingobject->get_host();

     pingobject->inc_pingssent();
     pingobject->inc_seqnr();
     process->setProcessChannelMode(QProcess::MergedChannels);
     process->start(command);

     QString data;

     while(process->waitForReadyRead())
         data.append(process->readAll());

     QString result = data.mid(data.lastIndexOf('=') + 2,data.indexOf('/',data.lastIndexOf('=')) - data.lastIndexOf('=')-2);

     pingobject->set_curRTT(result.toFloat());
     pingobject->set_nextpingtime(QDateTime().currentDateTime().addSecs(pingobject->get_delayBetweenPings()));
     if (pingobject->get_curRTT() > 0) pingobject->set_progress(pingobject->get_progress() + "!");
     else pingobject->set_progress(pingobject->get_progress() + ".");
     pingobject->set_threadstatus("finished");
 };
