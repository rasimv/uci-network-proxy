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

void MainWindow::setServer(Server *a)
{
    m_server = a;
    connect(m_server, SIGNAL(statusMessage(const QString &)), SLOT(onStatusMessage(const QString &)));
}

void MainWindow::on_pushButton_engineExecutableFilepath_clicked()
{
    const QString e(QFileDialog::getOpenFileName(this, windowTitle() + " - select engine executable"));
    m_ui->lineEdit_engineExecutableFilepath->setText(e);
}

void MainWindow::on_pushButton_start_clicked()
{
    Q_ASSERT(m_server != nullptr);
    m_server->setEngineExecutableFilepath(m_ui->lineEdit_engineExecutableFilepath->text());
    m_server->setAddressToListen(m_ui->lineEdit_addressToListen->text());
    m_server->start();
}

void MainWindow::on_pushButton_stop_clicked()
{
    m_server->stop();
}

void MainWindow::onStatusMessage(const QString &a)
{
    const auto t(m_ui->plainTextEdit_log->toPlainText());
    m_ui->plainTextEdit_log->setPlainText(t + a + "\n");
}
