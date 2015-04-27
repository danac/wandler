#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>

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

    // Menubar entries
    void on_actionExit_triggered();
    void on_actionAbout_triggered();

private:
    Ui::MainWindow* m_ui;
};

#endif // MAINWINDOW_H
