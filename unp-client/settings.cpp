#include "settings.h"

#include <QFile>
#include <QTextStream>

Settings::Settings(const QString &a_filepath)
{
    QFile l_file(a_filepath);
    if (!l_file.open(QIODevice::ReadOnly)) return;

    QTextStream l_stream(&l_file);
    int k = 0;
    while (!l_stream.atEnd())
    {
        processLine(l_stream.readLine());
        k++;
    }
}

Settings::~Settings()
{}

QString Settings::param(const QString &a_name) const
{
    const auto l_valueIt(m_params.find(a_name));
    if (l_valueIt == m_params.end()) return QString();
    return l_valueIt.value();
}

void Settings::processLine(const QString &a)
{
    const auto l_eq = a.indexOf("=");
    if (l_eq < 0) return;
    const auto l_key = a.mid(0, l_eq).simplified();
    if (l_key.isEmpty()) return;
    const QString l_value(l_eq + 1 < a.size() ? a.mid(l_eq + 1) : QString());
    m_params[l_key] = l_value;
}
