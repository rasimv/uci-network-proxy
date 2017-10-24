#include "connection.h"

Connection::Connection(QObject *a_parent) :
    QObject(a_parent)
{}

Connection::~Connection()
{}

void Connection::start()
{}

void Connection::socketOnReadyRead()
{}

void Connection::socketOnDisconnected()
{
    Q_ASSERT(m_socket != nullptr);
    m_socket->deleteLater();
    emit disconnected();
}

void  Connection::socketOnError(QAbstractSocket::SocketError a)
{}

void Connection::processOnStarted()
{}

void Connection::processOnReadyRead()
{}

void Connection::processFinished(int a_exitCode, QProcess::ExitStatus a_exitStatus)
{
    Q_ASSERT(m_socket != nullptr);
    m_socket->close();
}

void Connection::processOnErrorOccurred(QProcess::ProcessError a)
{}
