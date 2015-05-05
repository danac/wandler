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
    explicit JobDispatcher(int num_workers = 1, QObject* parent = 0);
	virtual ~JobDispatcher();
    Job popJob();
    void pushJob(const Job& job);
    bool active();
    void shutdown();
    void start();

public slots:
    void handleJobCompleted(Job result);

signals:
    void jobInProgress(Job job);
    void jobCompleted(Job job);
    void jobsFinished();

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
