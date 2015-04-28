#include <exception>
#include <unistd.h>

#include <QMutexLocker>
#include <QThread>

#include "worker.h"
#include "exceptions.h"
#include "jobdispatcher.h"
#include "job.h"

#define STR(x) #x
#define STRINGIFY(x) STR(x)

#define FFMPEG_EXE_STR STRINGIFY(FFMPEG_EXE)

Worker::Worker(JobDispatcher* dispatcher, QObject* parent) :
    QObject(parent), m_dispatcher(dispatcher)
{
}

void Worker::process(const Job& job)
{
//    qDebug(FFMPEG_EXE_STR);
    sleep(1);
}

void Worker::work()
{
    forever {
        try
        {
            Job job = m_dispatcher->popJob();
            process(job);
            emit jobCompleted(job);
        }
        catch(std::exception& error)
        {
            if(dynamic_cast<Exceptions::EndOfWork*>(&error))
            {
                break;
            }
        }
    }
    qDebug("finished");
    this->thread()->quit();
}


