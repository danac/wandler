#include "job.h"

Job::Job(const QString& sourcePath, const QString& destinationPath)
    :m_source(sourcePath), m_destination(destinationPath)
{
}

Job::Job()
    :m_source(""), m_destination("")
{
}

QString Job::getSourcePath() const
{
    return m_source;
}

QString Job::getDestinationPath() const
{
    return m_destination;
}
