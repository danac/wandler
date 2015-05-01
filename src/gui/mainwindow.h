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
    void handleStart();
    void handleJobCompleted(Job job);
    void handleJobsFinished();
    void handleJobInProgress(Job job);
    void handleToggleCustomOutputFolder(bool useCustomOutputFolder);
    void handleUpdateCustomOutputFolder();
    void handleAddFiles();
    void handleAddFolder();
    void handleBrowseCustomOutputFolder();
    void handleClearSelectedPending();

    // Menubar entries
    void on_actionExit_triggered();
    void on_actionAbout_triggered();

private:
    QStringList browseFiles();
    QString browseFolder();
    void initUi();
    void readUiSettings();

private:
    Ui::MainWindow* m_ui;
    JobDispatcher* m_jobDispatcher;
};

#endif // MAINWINDOW_H
