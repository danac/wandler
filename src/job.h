#ifndef JOB_H
#define JOB_H

#include <QString>
#include <QMetaType>

class Job
{
public:
    Job();
    Job(const QString& source, const QString& destination="");
    QString getSourcePath() const;
    QString getDestinationPath() const;

private:
    QString m_source;
    QString m_destination;
};

Q_DECLARE_METATYPE(Job)

#endif // JOB_H
