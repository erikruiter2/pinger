#ifndef PINGTASK_H
#define PINGTASK_H

#include <QThreadPool>
#include "PingObject.h"
#include <QProcess>

class PingTask : public QRunnable
 {
    public:
    PingObject * pingobject;
    void run();
 };

#endif // PINGTASK_H
