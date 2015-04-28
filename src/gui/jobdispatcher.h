#ifndef JOBLIST_H
#define JOBLIST_H

#include <QObject>

#include "job.h"

class WorkerPool;
template<typename> class QQueue;
class QMutex;
class QReadWriteLock;
class QWaitCondition;

class JobDispatcher : public QObject
{
    Q_OBJECT

public:
    explicit JobDispatcher(QObject* parent = 0);
    Job popJob();
    void pushJob(const Job& job);
    bool active();
    void shutdown();
    void start();

signals:
    void jobsCompleted();

private:
    typedef QQueue<Job> JobQueue;
    JobQueue* m_queue;
    WorkerPool* m_workerPool;
    bool m_active;
    QMutex* m_mutex;
    QReadWriteLock* m_readWriteLock;
    QWaitCondition* m_waitCondition;
};

#endif // JOBLIST_H
