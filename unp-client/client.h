#ifndef __CLIENT_H
#define __CLIENT_H

#include <QFile>
#include <QTcpSocket>

class Client : public QObject
{
    Q_OBJECT

public:
    explicit Client(QObject *a_parent = nullptr);
    virtual ~Client();

    void setAddress(const QString &a) { m_address = a; }
    void start();

signals:
    void disconnected();
    void error();

private slots:
    void stdinOnReadyRead();

    void socketOnConnected();
    void socketOnReadyRead();
    void socketOnDisconnected();
    void socketOnError(QAbstractSocket::SocketError a);

private:
    QString m_address;
    QFile m_stdin, m_stdout;
    QTcpSocket m_con;
    QByteArray m_buf;
};

#endif // __CLIENT_H
