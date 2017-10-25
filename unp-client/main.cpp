#include <QCoreApplication>
#include <QHostAddress>
#include <QTcpSocket>

int main(int a_argc, char *a_argv[])
{
    QCoreApplication a(a_argc, a_argv);
    QTcpSocket l_connection(&a);
    a.connect(&l_connection, SIGNAL(disconnected()), SLOT(quit()));
    l_connection.connectToHost(QHostAddress("127.0.0.1"), 12345);

    return a.exec();
}
