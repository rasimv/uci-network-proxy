#ifndef __CLIENT_H
#define __CLIENT_H

#include <QFile>
#include <QTcpSocket>
#include "stdinreader.h"

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
    void stdinOnNewData(const QByteArray &a);

    void socketOnConnected();
    void socketOnReadyRead();
    void socketOnDisconnected();
    void socketOnError(QAbstractSocket::SocketError a);

private:
    QString m_address;
    StdinReader m_stdin;
    QFile m_stdout;
    QTcpSocket m_con;
    QByteArray m_buf;
};

#endif // __CLIENT_H
