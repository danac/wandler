#ifndef JOBLIST_H
#define JOBLIST_H

#include <string>

#include <QObject>
#include <QQueue>
#include <QMutex>
#include <QWaitCondition>
#include <QReadWriteLock>

#include "job.h"

class JobDispatcher : public QObject
{
    Q_OBJECT

public:
    explicit JobDispatcher(QObject* parent = 0);
    Job popJob();
    void pushJob(const Job& job);
    void waitForJobs(QMutex &mutex);
    bool active();
    void active(bool flag);

private:
    QQueue<Job> m_queue;
    QMutex m_mutex;
    QReadWriteLock m_readWriteLock;
    QWaitCondition m_waitCondition;
    bool m_active;
};

#endif // JOBLIST_H
