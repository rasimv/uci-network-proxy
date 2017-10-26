#ifndef __SETTINGS_H
#define __SETTINGS_H

#include <QString>
#include <QMap>

class Settings
{
public:
    Settings(const QString &a_filepath);
    ~Settings();

    QString param(const QString &a_name) const;

private:
    void processLine(const QString &a);

    QMap<QString, QString> m_params;
};

#endif // __SETTINGS_H
