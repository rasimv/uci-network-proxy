#ifndef __SERVER_H
#define __SERVER_H

#include <QObject>
#include <QTcpServer>

class Connection;

class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(QObject *a_parent = nullptr);
    virtual ~Server();

    void setEngineExecutableFilepath(const QString &a) { m_engineExecutableFilepath = a; }
    void setAddressToListen(const QString &a) { m_addressToListen = a; }
    void start();
    void stop();

    QString engineExecutableFilepath() const { return m_engineExecutableFilepath; }

signals:
    void statusMessage(const QString &a);

private slots:
    void onAcceptError(QAbstractSocket::SocketError a);
    void onNewConnection();

private:
    QString m_engineExecutableFilepath, m_addressToListen;
    QTcpServer *m_server = nullptr;
    QSet<Connection *> m_cons;
};

#endif // __SERVER_H
