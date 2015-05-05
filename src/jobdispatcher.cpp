#include <QMutexLocker>
#include <QQueue>
#include <QMutex>
#include <QWaitCondition>
#include <QReadWriteLock>
#include <QMetaType>

#include "jobdispatcher.h"
#include "exceptions.h"
#include "workerpool.h"

JobDispatcher::JobDispatcher(int num_workers, QObject* parent) :
    QObject(parent),
    m_queue(new JobQueue),
    m_workerPool(new WorkerPool(this, num_workers, this)),
    m_active(true),
    m_mutex(new QMutex),
    m_readWriteLock(new QReadWriteLock),
    m_waitCondition(new QWaitCondition)
{
    qRegisterMetaType<Job>();
}

JobDispatcher::~JobDispatcher()
{
	delete m_waitCondition;
	delete m_readWriteLock;
	delete m_mutex;
	delete m_workerPool;
	delete m_queue;
}

void JobDispatcher::handleJobCompleted(Job result)
{
    emit jobCompleted(result);
}

Job JobDispatcher::popJob()
{
    QMutexLocker lock(m_mutex);
    if(m_queue->empty())
    {
        emit jobsFinished();
        m_waitCondition->wait(m_mutex);
    }
    if(!active())
    {
        throw Exceptions::EndOfWork();
    }
    Job job = m_queue->dequeue();
    emit jobInProgress(job);
    return job;
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
