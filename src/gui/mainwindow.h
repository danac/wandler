#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class JobDispatcher;
class QStringList;
class QString;
class Job;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

private slots:
    void startWork();
    void handleJobCompleted(Job job);
    void handleJobsFinished();
    void addFiles();
    void addFolder();
    void clearSelectedPending();

    // Menubar entries
    void on_actionExit_triggered();
    void on_actionAbout_triggered();

private:
    QStringList browseFiles();
    QString browseFolder();
    void initUi();
    void setDefaultSettings();

private:
    Ui::MainWindow* m_ui;
    JobDispatcher* m_jobDispatcher;
};

#endif // MAINWINDOW_H
