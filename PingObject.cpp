#include"PingObject.h"
#include<QDateTime>

PingObject::PingObject()
{
    id=0;
    avgRTT=-1;
    curRTT=-1;
    pingssent=0;
    sucessfullpings=0;
    host="";
    progress="";
    nextpingtime=QDateTime().currentDateTime();
    seqnr=0;
    threadstatus = "begin";
    delayBetweenPings=1;
}

QString PingObject::get_host() { return host;}
void PingObject::set_host(QString s) {host = s;}
QString PingObject::get_progress() {return progress;}
void PingObject::set_progress(QString s) { progress = s;}
int PingObject::get_pingssent() {return pingssent;}
void PingObject::inc_pingssent(){ pingssent++; }
float PingObject::get_avgRTT() { return avgRTT;}
float PingObject::get_curRTT() { return curRTT;}
void PingObject::set_avgRTT(float f) { avgRTT = f;}
void PingObject::set_curRTT(float f) { curRTT = f;}
void PingObject::set_nextpingtime(QDateTime i) { nextpingtime = i;}
QDateTime PingObject::get_nextpingtime() {return nextpingtime;}
int PingObject::get_id() {return id;}
void PingObject::set_id(int i) {id = i;}
void PingObject::set_threadstatus(QString s) { threadstatus = s; }
QString PingObject::get_threadstatus() { return threadstatus; }
void PingObject::set_delayBetweenPings(int i) { delayBetweenPings = i;}
int PingObject::get_delayBetweenPings() { return delayBetweenPings; }
int PingObject::get_seqnr() { return seqnr;}
void PingObject::inc_seqnr() { seqnr ++; }

QStringList PingObject::get_data() {
    QStringList temp;
    QString tempnum;
    temp << host;
    temp << tempnum.setNum(pingssent);
    temp << tempnum.setNum(avgRTT);
    temp << tempnum.setNum(curRTT);
    temp << progress;
    temp << threadstatus;

    return temp;
}
