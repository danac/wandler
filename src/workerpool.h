#ifndef WORKERPOOL_H
#define WORKERPOOL_H

#include <QObject>

#include "worker.h"

class QThread;
class Worker;
template<typename> class QList;

class JobDispatcher;

class WorkerPool : public QObject
{
    Q_OBJECT

public:
    explicit WorkerPool(JobDispatcher* dispatcher, int num_workers = 1, QObject* parent = 0);
    virtual ~WorkerPool();
    void start();

private:
    typedef QList<QThread*> ThreadList;
    typedef QList<Worker*> WorkerList;
    WorkerList* m_workers;
    ThreadList* m_threads;
};

#endif // WORKERPOOL_H
