
#ifndef QTREDIS_HPP
#define QTREDIS_HPP

#include <iostream>
#include <QThread>
#include <hiredis/adapters/qt.h>

#define FACE_CHANNEL "face-recognition"
class QTRedis : public QObject {
    Q_OBJECT

public:
    QThread* currentThread;
    QTRedis();
    virtual ~QTRedis();
    void start();

signals:
    void signalNewPerson(const QString& text);

public slots:
    void run();

private:
    
    redisAsyncContext * m_ctx;
    RedisQtAdapter m_adapter;

};

#endif /* QTREDIS_HPP */

