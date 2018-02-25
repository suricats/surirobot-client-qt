/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   APICaller.hpp
 * Author: alain
 *
 * Created on 25 février 2018, 19:22
 */

#ifndef APICALLER_HPP
#define APICALLER_HPP

#include <QtNetwork>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QThread>
#include <QString>
#include <QByteArray>
#include <iostream>

class APICaller : public QObject {
    Q_OBJECT
public:
    APICaller();
    APICaller(QString url);
    virtual ~APICaller();
    bool isBusy;
    virtual void start() const;
protected:
    QUrl url;
    QNetworkAccessManager* networkManager;
    QThread* currentThread;
public slots:
    virtual void sendRequest(QString text = "") = 0;
    virtual void receiveReply(QNetworkReply* reply) = 0;
signals:
    void newReply(QString text);

};

#endif /* APICALLER_HPP */

