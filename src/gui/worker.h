#ifndef WORKER_H
#define WORKER_H

#include <QObject>

#include "job.h"

class JobDispatcher;

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(JobDispatcher* dispatcher, QObject* parent = 0);

public slots:
    void work();

//signals:
//    void finished();

private:
    void process(const Job& job);

private:
    JobDispatcher* m_dispatcher;
};

#endif // WORKER_H
