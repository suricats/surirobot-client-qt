/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   QTRedis.hpp
 * Author: tberdy
 *
 * Created on 21 décembre 2017, 21:11
 */

#ifndef QTREDIS_HPP
#define QTREDIS_HPP

#include <iostream>
#include "lib/hiredis/include/adapters/qt.h"

class QTRedis : public QObject {
    Q_OBJECT

public:
    QTRedis();
    virtual ~QTRedis();
    

signals:
    void signalNewPerson(const QString& text);

public slots:
    void run();

private:
    redisAsyncContext * m_ctx;
    RedisQtAdapter m_adapter;

};

#endif /* QTREDIS_HPP */

