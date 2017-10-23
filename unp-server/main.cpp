#include "mainwindow.h"
#include <QApplication>

int main(int a_argc, char *a_argv[])
{
    QApplication a(a_argc, a_argv);
    MainWindow w;
    w.show();

    return a.exec();
}
