#include <QCoreApplication>
#include "client.h"

int main(int a_argc, char *a_argv[])
{
    QCoreApplication a(a_argc, a_argv);

    Client l_client;
    a.connect(&l_client, SIGNAL(disconnected()), SLOT(quit()));
    a.connect(&l_client, SIGNAL(error()), SLOT(quit()));
    l_client.setAddress("127.0.0.1:12345");
    l_client.start();

    return a.exec();
}
