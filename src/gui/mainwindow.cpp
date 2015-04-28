#include <QMessageBox>
#include <QStringList>
#include <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "jobdispatcher.h"
#include "job.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    m_jobDispatcher = new JobDispatcher(this);
    m_jobDispatcher->start();
    connect(m_jobDispatcher, SIGNAL(jobsCompleted()), this, SLOT(handleJobsCompleted()));
    connectUiSignals();
}

void MainWindow::connectUiSignals()
{
    connect(m_ui->pushButtonStart, SIGNAL(clicked()), this, SLOT(startWork()));
    connect(m_ui->pushButtonAddFiles, SIGNAL(clicked()), this, SLOT(addFiles()));
    connect(m_ui->pushButtonAddFolder, SIGNAL(clicked()), this, SLOT(addFolder()));
}

MainWindow::~MainWindow()
{
    m_jobDispatcher->shutdown();
    delete m_ui;
}

void MainWindow::addFiles()
{
    QStringList files = browseFiles();
}

void MainWindow::addFolder()
{
    QString dir = browseFolder();
}

void MainWindow::startWork()
{

    Job job1("Job 1");
    Job job2("Job 2");
    Job job3("Job 3");

    m_jobDispatcher->pushJob(job1);

    qDebug("mainStart");
}

void MainWindow::handleJobsCompleted()
{
    m_ui->tabWidgetSource->setEnabled(true);
    m_ui->pushButtonStart->setEnabled(true);
    m_ui->groupBoxOutput->setEnabled(true);
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "About", "About message");
}

QStringList MainWindow::browseFiles()
{
    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);
    QStringList fileNames;
    if (dialog.exec())
        fileNames = dialog.selectedFiles();
    return fileNames;
}

QString MainWindow::browseFolder()
{
    QString dir = QFileDialog::getExistingDirectory(this);
//    dialog.setDirectory(QDir::homePath());
//    dialog.setFileMode(QFileDialog::);
//    QStringList fileNames;
//    if (dialog.exec())
//        fileNames = dialog.selectedFiles();
    return dir;
}
