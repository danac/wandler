#include "worker.h"

#define STR(x) #x
#define STRINGIFY(x) STR(x)

#define FFMPEG_EXE_STR STRINGIFY(FFMPEG_EXE)

Worker::Worker(JobDispatcher* dispatcher, QObject* parent) :
    QObject(parent), m_dispatcher(dispatcher)
{
}

void Worker::process(const Job& job)
{
    qDebug(FFMPEG_EXE_STR);
    qDebug(job.getPath().c_str());
    emit finished();
}

void Worker::work()
{

}


