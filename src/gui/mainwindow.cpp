#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "jobdispatcher.h"
#include "job.h"
#include "workerpool.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    m_jobDispatcher = new JobDispatcher(this);
    connect(m_ui->pushButtonStart, SIGNAL(clicked()), this, SLOT(startWork()));
}

MainWindow::~MainWindow()
{
    m_jobDispatcher->shutdown();
    delete m_ui;
}

void MainWindow::startWork()
{

    Job job1("Job 1");
    Job job2("Job 2");
    Job job3("Job 3");

    m_jobDispatcher->pushJob(job1);

    qDebug("mainStart");
    m_jobDispatcher->start();
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "About", "About message");
}
