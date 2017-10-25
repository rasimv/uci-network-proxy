#include "connection.h"
#include "server.h"

Connection::Connection(QObject *a_parent) :
    QObject(a_parent),
    m_process(new QProcess())
{
    connect(m_process, SIGNAL(started()), SLOT(processOnStarted()));
    connect(m_process, SIGNAL(readyRead()), SLOT(processOnReadyRead()));
    connect(m_process, SIGNAL(finished(int, QProcess::ExitStatus)),
        SLOT(processFinished(int, QProcess::ExitStatus)));
    connect(m_process, SIGNAL(errorOccurred(QProcess::ProcessError)),
        SLOT(processOnErrorOccurred(QProcess::ProcessError)));
}

Connection::~Connection()
{
    disconnect(m_process, SIGNAL(started()), this, SLOT(processOnStarted()));
    disconnect(m_process, SIGNAL(readyRead()), this, SLOT(processOnReadyRead()));
    disconnect(m_process, SIGNAL(finished(int, QProcess::ExitStatus)),
        this, SLOT(processFinished(int, QProcess::ExitStatus)));
    disconnect(m_process, SIGNAL(errorOccurred(QProcess::ProcessError)),
        this, SLOT(processOnErrorOccurred(QProcess::ProcessError)));
    delete m_process;
}

void Connection::setSocket(QTcpSocket *a)
{
    Q_ASSERT(a != nullptr);
    m_socket = a;
    connect(m_socket, SIGNAL(readyRead()), SLOT(socketOnReadyRead()));
    connect(m_socket, SIGNAL(disconnected()), SLOT(socketOnDisconnected()));
    connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)),
        SLOT(socketOnError(QAbstractSocket::SocketError)));
}

void Connection::start()
{
    Q_ASSERT(m_process != nullptr);
    Server *const l_server = static_cast<Server *>(parent());
    m_process->start(l_server->engineExecutableFilepath());
}

void Connection::socketOnReadyRead()
{
    Q_ASSERT(m_socket != nullptr && m_process != nullptr);
    m_buf += m_socket->readAll();
    if (m_process->state() != QProcess::Running) return;
    m_process->write(m_buf); m_buf.clear();
}

void Connection::socketOnDisconnected()
{
    Q_ASSERT(m_socket != nullptr);
    m_socket->deleteLater();
    emit disconnected();
}

void  Connection::socketOnError(QAbstractSocket::SocketError a)
{}

void Connection::processOnStarted()
{
    Q_ASSERT(m_process != nullptr);
    if (m_buf.isEmpty()) return;
    m_process->write(m_buf); m_buf.clear();
}

void Connection::processOnReadyRead()
{
    Q_ASSERT(m_socket != nullptr && m_process != nullptr);
    m_socket->write(m_process->readAll()); m_socket->flush();
}

void Connection::processFinished(int a_exitCode, QProcess::ExitStatus a_exitStatus)
{
    Q_ASSERT(m_socket != nullptr);
    m_socket->close();
}

void Connection::processOnErrorOccurred(QProcess::ProcessError a)
{}
