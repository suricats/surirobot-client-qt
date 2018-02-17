/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   QTRedis.cpp
 * Author: tberdy
 * 
 * Created on 21 décembre 2017, 21:11
 */

#include "QTRedis.hpp"
#include <cstdio>
#include <string>
/*
QTRedis::QTRedis() {
}

QTRedis::~QTRedis() {
}

void onChange(redisAsyncContext*, void* r, void* privdata) {
    redisReply * reply = static_cast<redisReply *>(r);
    QTRedis * obj = static_cast<QTRedis*>(privdata);
    if (reply == nullptr) return;
    if (reply->type == REDIS_REPLY_ARRAY) {
        std::string type(reply->element[0]->str);
        std::string channel(reply->element[1]->str);
        
        if (type.compare("message") == 0 && channel.compare("face-recognition") == 0) {
            std::string message(reply->element[2]->str);
            emit obj->signalNewPerson(QString::fromUtf8(reply->element[2]->str));
            //emit obj->signalNewPerson();
        }
    }
    
    
}

void QTRedis::run() {

    m_ctx = redisAsyncConnect("localhost", 6379);

    if (m_ctx->err) {
        std::cerr << "Error: " << m_ctx->errstr << std::endl;
        redisAsyncFree(m_ctx);
        //emit finished();
    }

    m_adapter.setContext(m_ctx);
    redisAsyncCommand(m_ctx, onChange, this, "SUBSCRIBE face-recognition");
}
*/

