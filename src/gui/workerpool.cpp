#include "workerpool.h"

WorkerPool::WorkerPool(JobDispatcher* dispatcher, int num_workers, QObject* parent) :
    QObject(parent)
{
    for(int i(0); i < num_workers; ++i)
    {
        QThread* thread = new QThread(this);
        Worker* worker = new Worker(dispatcher, this);
        worker->moveToThread(thread);

        connect(thread, SIGNAL(started()), worker, SLOT(work()));
        connect(worker, SIGNAL(finished()), thread, SLOT(quit()));

        m_workers.append(worker);
        m_threads.append(thread);
    }
}

void WorkerPool::start()
{
    ThreadList::const_iterator i;
    for (i = m_threads.begin(); i!= m_threads.end(); ++i)
    {
        QThread* thread = *i;
        thread->start();
    }
}
