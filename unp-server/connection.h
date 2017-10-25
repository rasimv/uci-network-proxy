#ifndef __CONNECTION_H
#define __CONNECTION_H

#include <QObject>
#include <QTcpSocket>
#include <QProcess>

class Server;

class Connection: public QObject
{
    Q_OBJECT

public:
    explicit Connection(QObject *a_parent = nullptr);
    virtual ~Connection();

    void setSocket(QTcpSocket *a);
    void start();

signals:
    void disconnected();

private slots:
    void socketOnReadyRead();
    void socketOnDisconnected();
    void socketOnError(QAbstractSocket::SocketError a);

    void processOnStarted();
    void processOnReadyRead();
    void processFinished(int a_exitCode, QProcess::ExitStatus a_exitStatus);
    void processOnErrorOccurred(QProcess::ProcessError a);

private:
    QTcpSocket *m_socket = nullptr;
    QProcess *m_process = nullptr;
    QByteArray m_buf;
};

#endif // __CONNECTION_H
