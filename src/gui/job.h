#ifndef JOB_H
#define JOB_H

#include <string>

class Job
{
public:
    Job(const std::string& path);
    std::string getPath() const;

private:
    std::string m_path;
};

class EndOfJobs : public Job
{

};

#endif // JOB_H
