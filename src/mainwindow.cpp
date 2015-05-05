#include <cassert>

#include <QMessageBox>
#include <QStringList>
#include <QFileDialog>
#include <QString>
#include <QDir>

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
    m_jobDispatcher = new JobDispatcher(1, this);
    m_jobDispatcher->start();

    connect(m_jobDispatcher, SIGNAL(jobsFinished()), this, SLOT(handleJobsFinished()));
    connect(m_jobDispatcher, SIGNAL(jobInProgress(Job)), this, SLOT(handleJobInProgress(Job)));
    connect(m_jobDispatcher, SIGNAL(jobCompleted(Job)), this, SLOT(handleJobCompleted(Job)));

    initUi();
    readUiSettings();
}

void MainWindow::readUiSettings()
{
    Settings::customOutputFolder = m_ui->lineEditCustomOutputFolder->text();
}

void MainWindow::initUi()
{
    m_ui->lineEditCustomOutputFolder->setText(Settings::defaultCustomOutputFolder);
    connect(m_ui->pushButtonStart, SIGNAL(clicked()), this, SLOT(handleStart()));
    connect(m_ui->pushButtonAddFiles, SIGNAL(clicked()), this, SLOT(handleAddFiles()));
    connect(m_ui->pushButtonAddFolder, SIGNAL(clicked()), this, SLOT(handleAddFolder()));
    connect(m_ui->pushButtonClearPending, SIGNAL(clicked()), this, SLOT(handleClearSelectedPending()));
    connect(m_ui->pushButtonBrowseCustomOutputFolder, SIGNAL(clicked()), this, SLOT(handleBrowseCustomOutputFolder()));
    connect(m_ui->radioButtonCustomOutputFolder, SIGNAL(toggled(bool)), this, SLOT(handleToggleCustomOutputFolder(bool)));
    connect(m_ui->lineEditCustomOutputFolder, SIGNAL(editingFinished()), this, SLOT(handleUpdateCustomOutputFolder()));
}

void MainWindow::handleToggleCustomOutputFolder(bool useCustomOutputFolder)
{
    Settings::useCustomOutputFolder = useCustomOutputFolder;
}

void MainWindow::handleUpdateCustomOutputFolder()
{
    QString newPath = m_ui->lineEditCustomOutputFolder->text();
    QDir newDir(newPath);
    bool isPathValid = newDir.isAbsolute() && newDir.exists();

    if(isPathValid)
    {
        Settings::customOutputFolder = newPath;
    }
    else
    {
        QMessageBox::warning(this, "Error", "The path must be absolute and point to an existing directory.");
        m_ui->lineEditCustomOutputFolder->setText(Settings::customOutputFolder);
    }
}

MainWindow::~MainWindow()
{
    m_jobDispatcher->shutdown();
	delete m_jobDispatcher;
    delete m_ui;
}

void MainWindow::handleAddFiles()
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

void MainWindow::handleBrowseCustomOutputFolder()
{
    QString dir = browseFolder();
    m_ui->lineEditCustomOutputFolder->setText(dir);
    readUiSettings();
}

void MainWindow::handleClearSelectedPending()
{
    QListWidget* listWidget = m_ui->listWidgetPending;
    QList<QListWidgetItem*> selection = listWidget->selectedItems();
    QList<QListWidgetItem*>::iterator i;
    for(i = selection.begin(); i != selection.end(); ++i)
    {
        listWidget->takeItem(listWidget->row(*i));
    }

}

void MainWindow::handleAddFolder()
{
    QString dir = browseFolder();
}

void MainWindow::handleStart()
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
    QString sourcePath = job.getSourcePath();
//    QString destinationPath = job.getDestinationPath();

    QListWidget* listWidgetInProgress = m_ui->listWidgetInProgress;
    QListWidget* listWidgetCompleted = m_ui->listWidgetCompleted;

    QList<QListWidgetItem*> itemFound = listWidgetInProgress->findItems(sourcePath, Qt::MatchExactly);
    assert(itemFound.size() == 1);

    listWidgetInProgress->takeItem(listWidgetInProgress->row(itemFound[0]));
    new QListWidgetItem(sourcePath, listWidgetCompleted);
}

void MainWindow::handleJobInProgress(Job job)
{
    QString sourcePath = job.getSourcePath();

    QListWidget* listWidgetPending = m_ui->listWidgetPending;
    QListWidget* listWidgetInProgress= m_ui->listWidgetInProgress;

    QList<QListWidgetItem*> itemFound = listWidgetPending->findItems(sourcePath, Qt::MatchExactly);
    assert(itemFound.size() == 1);
    listWidgetPending->takeItem(listWidgetPending->row(itemFound[0]));

    new QListWidgetItem(sourcePath, listWidgetInProgress);

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
