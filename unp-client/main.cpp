#include <QCoreApplication>
#include "client.h"
#include "settings.h"
#include "logger.h"
#include <QFileInfo>
#include <QDir>

int main(int a_argc, char *a_argv[])
{
    QCoreApplication a(a_argc, a_argv);

    const QFileInfo l_settingsFI(QDir(a.applicationDirPath()), "settings.txt");
    const Settings l_settings(l_settingsFI.absoluteFilePath());
    const QString l_address(l_settings.param("address"));

    Logger l_logger;
    const QFileInfo l_logFI(QDir(a.applicationDirPath()), "log.txt");
    l_logger.open(l_logFI.absoluteFilePath());

    Client l_client;
    QObject::connect(&l_client, SIGNAL(disconnected()), &a, SLOT(quit()));
    QObject::connect(&l_client, SIGNAL(error()), &a, SLOT(quit()));
    QObject::connect(&l_client, SIGNAL(log(const QString &)), &l_logger, SLOT(message(const QString &)));
    l_client.setAddress(l_address);
    l_client.start();

    return a.exec();
}
