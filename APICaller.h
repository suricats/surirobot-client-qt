/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   APICaller.h
 * Author: Alain BERRIER
 *
 * Created on 8 février 2018, 20:40
 */

#ifndef APICALLER_H
#define APICALLER_H

#include <QtCore/qthread.h>

#include <QtWidgets>
#include <QtNetwork>

#include <QNetworkReply>
#include <QDebug>
#include <QObject>
#include <QNetworkAccessManager>
#include <QThread>
#include <QWaitCondition>
#include <QMutex>    
#include <iostream>

class APICaller : public QObject {
    Q_OBJECT

    QNetworkAccessManager* nam;
    QMutex syncPause;
    QWaitCondition pauseCond;

public:
    explicit APICaller(QObject *parent = 0);

public slots:

    void doSend();
    void set(QThread* thread);
    void finishedSlot(QNetworkReply* reply);
};
#endif /* APICALLER_H */

