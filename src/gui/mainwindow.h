#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class JobDispatcher;
class QStringList;
class QString;

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
    void handleJobsCompleted();
    void addFiles();
    void addFolder();

    // Menubar entries
    void on_actionExit_triggered();
    void on_actionAbout_triggered();

private:
    QStringList browseFiles();
    QString browseFolder();
    void connectUiSignals();

private:
    Ui::MainWindow* m_ui;
    JobDispatcher* m_jobDispatcher;
};

#endif // MAINWINDOW_H
