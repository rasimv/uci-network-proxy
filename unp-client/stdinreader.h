#ifndef __STDINREADER_H
#define __STDINREADER_H

#include <QObject>
#include <memory>
#include <atomic>
#include <mutex>
#include <thread>

class StdinReader : public QObject
{
    Q_OBJECT

    friend class SharedData;

    struct SharedData
    {
        SharedData() : m_shutdown(false) { m_deferMutex.lock(); }
        std::atomic<bool> m_shutdown;
        std::mutex m_deferMutex, m_emitMutex;
    };

public:
    explicit StdinReader(QObject *a_parent = nullptr);
    virtual ~StdinReader();

signals:
    void newDataDirect(QByteArray a);
    void newData(const QByteArray &a);

private slots:
    void newDataQueued(QByteArray a);

private:
    void newDataInternal(const QByteArray &a);

    static void workerFunc(std::shared_ptr<SharedData> a_sd, StdinReader *a_key);

    std::shared_ptr<SharedData> m_sd;
    std::thread m_worker;
};

#endif // __STDINREADER_H
