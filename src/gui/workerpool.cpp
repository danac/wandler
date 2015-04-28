#include <QThread>
#include <QList>

#include "workerpool.h"

WorkerPool::WorkerPool(JobDispatcher* dispatcher, int num_workers, QObject* parent) :
    QObject(parent), m_workers(new WorkerList), m_threads(new ThreadList)
{
    for(int i(0); i < num_workers; ++i)
    {
        QThread* thread = new QThread();
        Worker* worker = new Worker(dispatcher);
        worker->moveToThread(thread);

//        connect(worker, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
        connect(thread, SIGNAL(started()), worker, SLOT(work()));

        m_workers->append(worker);
        m_threads->append(thread);
    }
}

void WorkerPool::start()
{
    ThreadList::const_iterator i;
    for (i = m_threads->begin(); i!= m_threads->end(); ++i)
    {
        QThread* thread = *i;
        thread->start();
    }
}

WorkerPool::~WorkerPool()
{
    {
        ThreadList::const_iterator i;
        for (i = m_threads->begin(); i!= m_threads->end(); ++i)
        {
            QThread* thread = *i;
            thread->wait();
            delete thread;
        }
    }
    {
        WorkerList::const_iterator i;
        for (i = m_workers->begin(); i!= m_workers->end(); ++i)
        {
            Worker* worker= *i;
            delete worker;
        }
    }
    delete m_threads;
    delete m_workers;
}
