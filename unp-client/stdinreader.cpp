#include "stdinreader.h"
#include <QFile>

StdinReader::StdinReader(QObject *a_parent) :
    QObject(a_parent),
    m_sd(std::make_shared<SharedData>()),
    m_worker(&StdinReader::workerFunc, m_sd, this)
{
    connect(this, SIGNAL(newDataDirect(QByteArray)), SLOT(newDataQueued(QByteArray)), Qt::QueuedConnection);
    m_sd->m_deferMutex.unlock();
}

StdinReader::~StdinReader()
{
    m_sd->m_shutdown = true;
    std::lock_guard<std::mutex>(m_sd->m_emitMutex);
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

void StdinReader::workerFunc(std::shared_ptr<SharedData> a_sd, StdinReader *a_key)
{
    Q_ASSERT(a_key != nullptr);
    const std::lock_guard<std::mutex> l_lock(a_sd->m_deferMutex);
    QFile l_stdin;
    l_stdin.open(stdin, QIODevice::ReadOnly);
    while (!a_sd->m_shutdown)
    {
        const QByteArray l_line(l_stdin.readLine(128 * 1024));
        const std::lock_guard<std::mutex> l_lock(a_sd->m_emitMutex);
        if (a_sd->m_shutdown) return;
        a_key->newDataInternal(l_line);
    }
}
