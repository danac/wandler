#include <QMutexLocker>

#include "jobdispatcher.h"

JobDispatcher::JobDispatcher(QObject* parent) :
    QObject(parent), m_active(true)
{
}

Job JobDispatcher::popJob()
{
    QMutexLocker lock(&m_mutex);
    return m_queue.dequeue();
}

void JobDispatcher::pushJob(const Job& job)
{
    QMutexLocker lock(&m_mutex);
    m_queue.enqueue(job);
    m_waitCondition.wakeOne();
}

void JobDispatcher::waitForJobs(QMutex &mutex)
{
    mutex.lock();
    m_waitCondition.wait(&mutex);
}

bool JobDispatcher::active()
{
    m_readWriteLock.lockForRead();
    return m_active;
}

void JobDispatcher::active(bool flag)
{
    m_readWriteLock.lockForWrite();
    m_active = flag;
}
