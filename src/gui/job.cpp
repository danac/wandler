#include "job.h"

Job::Job(const QString& path)
    :m_path(path)
{
}

Job::Job()
    :m_path("")
{
}

QString Job::getPath() const
{
    return m_path;
}
