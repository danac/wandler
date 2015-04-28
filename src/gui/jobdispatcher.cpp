#include <QMutexLocker>
#include <QQueue>
#include <QMutex>
#include <QWaitCondition>
#include <QReadWriteLock>

#include "jobdispatcher.h"
#include "exceptions.h"
#include "workerpool.h"

JobDispatcher::JobDispatcher(QObject* parent) :
    QObject(parent),
    m_queue(new JobQueue),
    m_workerPool(new WorkerPool(this, 1, this)),
    m_active(true),
    m_mutex(new QMutex),
    m_readWriteLock(new QReadWriteLock),
    m_waitCondition(new QWaitCondition)
{
}

Job JobDispatcher::popJob()
{
    QMutexLocker lock(m_mutex);
    if(m_queue->empty())
    {
        m_waitCondition->wait(m_mutex);
    }
    if(!active())
    {
        throw Exceptions::EndOfWork();
    }
    return m_queue->dequeue();
}

void JobDispatcher::pushJob(const Job& job)
{
    QMutexLocker lock(m_mutex);
    m_queue->enqueue(job);
    m_waitCondition->wakeOne();
}

bool JobDispatcher::active()
{
    m_readWriteLock->lockForRead();
    bool state = m_active;
    m_readWriteLock->unlock();
    return state;
}

void JobDispatcher::shutdown()
{
    {
        m_readWriteLock->lockForWrite();
        m_active = false;
        m_readWriteLock->unlock();
    }
    m_waitCondition->wakeAll();
}

void JobDispatcher::start()
{
    m_workerPool->start();
}
