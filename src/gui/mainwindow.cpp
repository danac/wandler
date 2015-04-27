#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "jobdispatcher.h"
#include "workerpool.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    connect(m_ui->pushButtonStart, SIGNAL(clicked()), this, SLOT(startWork()));
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::startWork()
{
    JobDispatcher jobDispatcher;
    WorkerPool workerPool(&jobDispatcher, 1);
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "About", "About message");
}
