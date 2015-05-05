#include <exception>
#include <QMutexLocker>
#include <QThread>
#include <QString>
#include <QStringList>
#include <QFileInfo>
#include <QDir>
#include <QProcess>
#include <QCoreApplication>

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
    QString sourcePath = job.getSourcePath();
    QFileInfo fileInfo(sourcePath);
    QString destinationFileName = fileInfo.baseName() + ".mp3";
    QString outputFolder("");
    if(Settings::useCustomOutputFolder)
    {
        outputFolder = Settings::customOutputFolder;
    }
    else
    {
        outputFolder = fileInfo.dir().absolutePath();
    }
    QString destinationPath = QDir::cleanPath(outputFolder + QDir::separator() + destinationFileName);

    QStringList ffmpegArgs;
    ffmpegArgs << "-y" << "-i" << sourcePath << "-q" << "0" << destinationPath;

    QString ffmpegExeStr = FFMPEG_EXE_STR;
	QDir ffmpegExeDir(ffmpegExeStr);
	QString ffmpegExePath = "";

	if(ffmpegExeDir.isAbsolute())
	{
		ffmpegExePath = ffmpegExeStr;
	}
	else
	{
		QString rootPath = QCoreApplication::applicationDirPath();
		ffmpegExePath = QDir::cleanPath(rootPath + QDir::separator() + ffmpegExeStr);
	}
    QProcess process;
    process.start(ffmpegExePath, ffmpegArgs);
    process.waitForFinished();
    QString output = process.readAllStandardOutput();

    Job result(sourcePath, destinationPath);
    return result;
}

void Worker::work()
{
    forever {
        try
        {
            Job job = m_dispatcher->popJob();
            emit jobInProgress(job);

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
    this->thread()->quit();
}


