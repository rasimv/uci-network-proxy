#include "server.h"
#include <QUrl>
#include "connection.h"
#include <memory>

Server::Server(QObject *a_parent) :
    QObject(a_parent)
{}

Server::~Server()
{
    stop();
}

void Server::start()
{
    stop();

    const QUrl l_asUrl(QString("http://") + m_addressToListen);
    const QHostAddress l_hostAddr(l_asUrl.host());
    const QString l_host(l_hostAddr.toString());
    const QString l_messageAddress(l_host + QString(":%1").arg(l_asUrl.port()));

    m_server = new QTcpServer(this);
    connect(m_server, SIGNAL(acceptError(QAbstractSocket::SocketError)), SLOT(onAcceptError(QAbstractSocket::SocketError)));
    connect(m_server, SIGNAL(newConnection()), SLOT(onNewConnection()));

    if (m_server->listen(l_hostAddr, l_asUrl.port()))
        emit statusMessage(QString("Started: ") + l_messageAddress);
    else
        emit statusMessage(QString("Failed: ") + l_messageAddress);
}

void Server::stop()
{
    const size_t q = m_cons.size();
    if (m_server == nullptr) return;
    for (auto q : m_cons) delete q;
    m_cons.clear();
    delete m_server; m_server = nullptr;
}

void Server::onAcceptError(QAbstractSocket::SocketError)
{}

void Server::onNewConnection()
{
    for (auto x = m_server->nextPendingConnection(); x != nullptr; x = m_server->nextPendingConnection())
    {
        auto q(std::make_unique<Connection>(this));
        connect(q.get(), SIGNAL(disconnected()), SLOT(onDisconnected()));
        q->setSocket(x);
        m_cons.insert(q.get());
        q.release()->start();
        emit statusMessage(QString("Incoming: %1:%2").arg(x->peerAddress().toString()).arg(x->peerPort()));
    }
}

void Server::onDisconnected()
{
    m_cons.remove(static_cast<Connection *>(sender()));
    delete sender();
}
