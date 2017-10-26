#ifndef __LOGGER_H
#define __LOGGER_H

#include <QObject>
#include <QFile>
#include <QTextStream>

class Logger : public QObject
{
    Q_OBJECT

public:
    explicit Logger(QObject *a_parent = nullptr);
    virtual ~Logger();

    bool open(const QString &a_filepath);

public slots:
    void message(const QString &a);

private:
    QFile m_file;
    QTextStream m_stream;
};

#endif // __LOGGER_H
