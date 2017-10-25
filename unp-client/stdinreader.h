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
    typedef void (*CallbackFunc)(StdinReader *a_key, const QByteArray &a);

    struct SharedData
    {
        SharedData(CallbackFunc a) : m_shutdown(false), m_callback(a) { m_mutex.lock(); }
        std::mutex m_mutex;
        std::atomic<bool> m_shutdown;
        std::atomic<CallbackFunc> m_callback;
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

    static void newDataFunc(StdinReader *a_key, const QByteArray &a);
    static void stubFunc(StdinReader *a_key, const QByteArray &a);
    static void workerFunc(std::shared_ptr<SharedData> a_sd, StdinReader *a_key);

    std::shared_ptr<SharedData> m_sd;
    std::thread m_worker;
};

#endif // __STDINREADER_H
