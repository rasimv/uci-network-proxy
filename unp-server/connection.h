#ifndef __CONNECTION_H
#define __CONNECTION_H

#include <QObject>

class Connection: public QObject
{
    Q_OBJECT

public:
    explicit Connection(QObject *a_parent = nullptr);
    ~Connection();
};

#endif // __CONNECTION_H
