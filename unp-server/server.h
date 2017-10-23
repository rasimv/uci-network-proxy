#ifndef __SERVER_H
#define __SERVER_H

#include <QObject>

class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(QObject *a_parent = nullptr);
    ~Server();
};

#endif // __SERVER_H
