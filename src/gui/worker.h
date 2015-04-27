#ifndef WORKER_H
#define WORKER_H

#include <QObject>

#include "job.h"
#include "jobdispatcher.h"

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(JobDispatcher* dispatcher, QObject* parent = 0);

signals:
    void finished();
    void error(QString err);

public slots:
    void work();

private:
    void process(const Job& job);

private:
    JobDispatcher* m_dispatcher;

};

#endif // WORKER_H
