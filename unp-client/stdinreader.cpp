#include "stdinreader.h"
#include <QFile>

StdinReader::StdinReader(QObject *a_parent) :
    QObject(a_parent),
    m_sd(std::make_shared<SharedData>(&StdinReader::newDataFunc)),
    m_worker(&StdinReader::workerFunc, m_sd, this)
{
    connect(this, SIGNAL(newDataDirect(QByteArray)), SLOT(newDataQueued(QByteArray)));
    m_sd->m_mutex.unlock();
}

StdinReader::~StdinReader()
{
    m_sd->m_shutdown = true;
    m_sd->m_callback = &StdinReader::stubFunc;
    m_worker.detach();
}

void StdinReader::newDataQueued(QByteArray a)
{
    emit newData(a);
}

void StdinReader::newDataInternal(const QByteArray &a)
{
    emit newDataDirect(a);
}

void StdinReader::newDataFunc(StdinReader *a_key, const QByteArray &a)
{
    Q_ASSERT(a_key != nullptr);
    a_key->newDataInternal(a);
}

void StdinReader::stubFunc(StdinReader *, const QByteArray &)
{}

void StdinReader::workerFunc(std::shared_ptr<SharedData> a_sd, StdinReader *a_key)
{
    Q_ASSERT(a_key != nullptr);
    const std::lock_guard<std::mutex> l_lock(a_sd->m_mutex);
    QFile l_stdin;
    l_stdin.open(stdin, QIODevice::ReadOnly);
    while (!a_sd->m_shutdown)
    {
        const QByteArray l_line(l_stdin.readLine(128 * 1024));
        const CallbackFunc l_func = a_sd->m_callback;
        l_func(a_key, l_line);
    }
}
