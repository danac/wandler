#include "job.h"

Job::Job(const std::string& path)
    :m_path(path)
{
}

std::string Job::getPath() const
{
    return m_path;
}
