#ifndef __MAINWINDOW_H
#define __MAINWINDOW_H

#include <QWidget>
#include "server.h"

namespace Ui { class MainWindow; }

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *a_parent = nullptr);
    virtual ~MainWindow();

    void setServer(Server *a);

private slots:
    void on_pushButton_engineExecutableFilepath_clicked();
    void on_pushButton_start_clicked();
    void on_pushButton_stop_clicked();

    void onStatusMessage(const QString &a);

private:
    Ui::MainWindow *m_ui;
    Server *m_server = nullptr;
};

#endif // __MAINWINDOW_H
