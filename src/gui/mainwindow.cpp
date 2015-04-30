#include <cassert>

#include <QMessageBox>
#include <QStringList>
#include <QFileDialog>
#include <QString>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "jobdispatcher.h"
#include "job.h"
#include "settings.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    m_jobDispatcher = new JobDispatcher(this);
    m_jobDispatcher->start();
    connect(m_jobDispatcher, SIGNAL(jobsFinished()), this, SLOT(handleJobsFinished()));
    connect(m_jobDispatcher, SIGNAL(jobCompleted(Job)), this, SLOT(handleJobCompleted(Job)));
    initUi();
    setDefaultSettings();
}

void MainWindow::setDefaultSettings()
{
    Settings::outputFolder = m_ui->lineEditOutputFolder->text();
}

void MainWindow::initUi()
{
    m_ui->lineEditOutputFolder->setText(QDir::home().absolutePath());
    connect(m_ui->pushButtonStart, SIGNAL(clicked()), this, SLOT(startWork()));
    connect(m_ui->pushButtonAddFiles, SIGNAL(clicked()), this, SLOT(addFiles()));
    connect(m_ui->pushButtonAddFolder, SIGNAL(clicked()), this, SLOT(addFolder()));
    connect(m_ui->pushButtonClearPending, SIGNAL(clicked()), this, SLOT(clearSelectedPending()));
}

MainWindow::~MainWindow()
{
    m_jobDispatcher->shutdown();
    delete m_ui;
}

void MainWindow::addFiles()
{
    QStringList files = browseFiles();
    QStringList::const_iterator i;
    for(i = files.begin(); i != files.end(); ++i)
    {
        QString path = *i;
        QListWidget* listWidget = m_ui->listWidgetPending;
        new QListWidgetItem(path, listWidget);
    }
}

void MainWindow::clearSelectedPending()
{
    QListWidget* listWidget = m_ui->listWidgetPending;
    QList<QListWidgetItem*> selection = listWidget->selectedItems();
    QList<QListWidgetItem*>::iterator i;
    for(i = selection.begin(); i != selection.end(); ++i)
    {
        listWidget->takeItem(listWidget->row(*i));
    }

}

void MainWindow::addFolder()
{
    QString dir = browseFolder();
}

void MainWindow::startWork()
{
    QListWidget* listWidget = m_ui->listWidgetPending;
    if(listWidget->count() == 0)
    {
        handleJobsFinished();
    }
    else
    {
        for(int i(0); i < listWidget->count(); ++i)
        {
            QListWidgetItem* item = listWidget->item(i);
            QString path = item->text();

            Job job(path);
            m_jobDispatcher->pushJob(job);
        }
    }
}

void MainWindow::handleJobCompleted(Job job)
{
    qDebug("Completed: ");
    qDebug(job.getDestinationPath().toStdString().c_str());

    QString sourcePath = job.getSourcePath();
    QString destinationPath = job.getDestinationPath();

    QListWidget* listWidgetPending = m_ui->listWidgetPending;
    QListWidget* listWidgetCompleted = m_ui->listWidgetCompleted;

    QList<QListWidgetItem*> itemFound = listWidgetPending->findItems(sourcePath, Qt::MatchExactly);
    assert(itemFound.size() == 1);

    listWidgetPending->takeItem(listWidgetPending->row(itemFound[0]));
    new QListWidgetItem(destinationPath, listWidgetCompleted);
}

void MainWindow::handleJobsFinished()
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
