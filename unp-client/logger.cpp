#include "logger.h"

Logger::Logger(QObject *a_parent) :
    QObject(a_parent)
{}

Logger::~Logger()
{}

bool Logger::open(const QString &a_filepath)
{
    m_file.setFileName(a_filepath);
    const bool o = m_file.open(QIODevice::WriteOnly);
    m_stream.setDevice(&m_file);
    return o;
}

void Logger::message(const QString &a)
{
    if (!m_file.isOpen()) return;
    m_stream << a;
#ifdef Q_OS_WIN
    m_stream << "\r";
#endif
    m_stream << "\n";
    m_stream.flush();
}
