#include "mainwindow.h"
#include <QApplication>
#include "server.h"

int main(int a_argc, char *a_argv[])
{
    QApplication a(a_argc, a_argv);
    Server s;
    MainWindow w;
    w.setServer(&s);
    w.show();

    return a.exec();
}
