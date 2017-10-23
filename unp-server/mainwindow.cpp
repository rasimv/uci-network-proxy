#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *a_parent) :
    QWidget(a_parent),
    m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::on_pushButton_engineExecutableFilepath_clicked()
{
    const QString e(QFileDialog::getOpenFileName(this, windowTitle() + " - select engine executable"));
    m_ui->lineEdit_engineExecutableFilepath->setText(e);
}
