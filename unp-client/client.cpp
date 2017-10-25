#include "client.h"
#include <QByteArray>
#include <QUrl>
#include <QHostAddress>
#include <QTimer>

Client::Client(QObject *a_parent) :
    QObject(a_parent)
{}

Client::~Client()
{}

void Client::start()
{
    connect(&m_stdin, SIGNAL(readyRead()), SLOT(stdinOnReadyRead()));
    m_stdin.open(stdin, QIODevice::ReadOnly);
    m_stdout.open(stdout, QIODevice::WriteOnly);

    connect(&m_con, SIGNAL(connected()), SLOT(socketOnConnected()));
    connect(&m_con, SIGNAL(readyRead()), SLOT(socketOnReadyRead()));
    connect(&m_con, SIGNAL(disconnected()), SLOT(socketOnDisconnected()));
    connect(&m_con, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(socketOnError(QAbstractSocket::SocketError)));

    const QUrl l_asUrl(QString("http://") + m_address);
    const QHostAddress l_hostAddr(l_asUrl.host());
    //const QString l_host(l_hostAddr.toString());
    //const QString l_messageAddress(l_host + QString(":%1").arg(l_asUrl.port()));

    m_con.connectToHost(l_hostAddr, l_asUrl.port());
}

void Client::stdinOnReadyRead()
{
    m_buf += m_stdin.readAll();
    if (m_con.state() != QAbstractSocket::ConnectedState) return;
    m_con.write(m_buf); m_buf.clear();
}

void Client::socketOnConnected()
{
    if (m_buf.isEmpty()) return;
    m_con.write(m_buf); m_buf.clear();
}

void Client::socketOnReadyRead()
{
    m_stdout.write(m_con.readAll());
}

void Client::socketOnDisconnected()
{
    QTimer::singleShot(0, this, [&]() { emit disconnected(); });
}

void Client::socketOnError(QAbstractSocket::SocketError a)
{
    QTimer::singleShot(0, this, [&]() { emit error(); });
}
