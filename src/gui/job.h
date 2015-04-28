#ifndef JOB_H
#define JOB_H

#include <QString>
#include <QMetaType>

class Job
{
public:
    Job();
    Job(const QString& path);
    QString getPath() const;

private:
    QString m_path;
};

Q_DECLARE_METATYPE(Job)

#endif // JOB_H
