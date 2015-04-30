#include <exception>
#include <unistd.h>

#include <QMutexLocker>
#include <QThread>
#include <QString>
#include <QFileInfo>
#include <QDir>

#include "worker.h"
#include "exceptions.h"
#include "jobdispatcher.h"
#include "job.h"
#include "settings.h"

#define STR(x) #x
#define STRINGIFY(x) STR(x)

#define FFMPEG_EXE_STR STRINGIFY(FFMPEG_EXE)

Worker::Worker(JobDispatcher* dispatcher, QObject* parent) :
    QObject(parent), m_dispatcher(dispatcher)
{
}

Job Worker::process(const Job& job)
{
    QString path = job.getSourcePath();
    QFileInfo fileInfo(path);
    QString baseName = fileInfo.baseName();
    QString outputFolder = Settings::outputFolder;
    QString destinationPath = QDir::cleanPath(outputFolder + QDir::separator() + baseName);
    qDebug(destinationPath.toStdString().c_str());

//    qDebug(FFMPEG_EXE_STR);
    sleep(1);
    return job;
}

void Worker::work()
{
    forever {
        try
        {
            Job job = m_dispatcher->popJob();
            Job result = process(job);
            emit jobCompleted(result);
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


