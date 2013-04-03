#ifndef PINGOBJECT_H
#define PINGOBJECT_H

#include<QWidget>
#include<QString>
#include<QStringList>
#include<QDateTime>
class PingObject: public QObject
{
    Q_OBJECT

public:
    PingObject();



    QString get_host();
    void set_host(QString s);
    QString get_progress();
    void set_progress(QString s);
    int get_pingssent();
    void inc_pingssent();
    void inc_seqnr();
    int get_seqnr();
    float get_avgRTT();
    float get_curRTT();
    void set_avgRTT(float f);
    void set_curRTT(float f);
    void set_nextpingtime(QDateTime i);
    QDateTime get_nextpingtime();
    int get_id();
    void set_id(int i);
    void set_threadstatus(QString s);
    void set_delayBetweenPings(int i);
    int get_delayBetweenPings();
    QString get_threadstatus();
    QStringList get_data();

public slots:

private:
    int id;
    float avgRTT;
    float curRTT;
    int pingssent;
    int sucessfullpings;
    QString host;
    QString progress;
    QDateTime nextpingtime;
    QString threadstatus;
    int seqnr;
    int delayBetweenPings;



};
#endif // PINGOBJECT_H
