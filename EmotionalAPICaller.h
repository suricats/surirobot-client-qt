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

#ifndef EMOTIONALAPICALLER_H
#define EMOTIONALAPICALLER_H

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
#include <vector>
#include <QtMultimedia/QtMultimedia>
#include <QtMultimedia/QCamera>
#include <QtMultimedia/QCameraInfo>
#include <QTime>

class EmotionalAPICaller : public QObject {
    Q_OBJECT
private:
    QNetworkAccessManager* networkManager;
    QThread* currentThread;
    QCamera* camera;
    QCameraImageCapture* recorder;
    QTimer* captureTimer;
    std::vector<QString> imageVec;
public:
    bool isBusy;
    explicit EmotionalAPICaller(QObject *parent = 0);
    virtual ~EmotionalAPICaller();
    void start();
public slots:
    void sendRequest();
    void receiveReply(QNetworkReply* reply);
    void captureImage();
    void imageCaptured(int id, const QImage& preview);
signals:
    
    void messageChanged(QString text);

};
#endif /* APICALLER_H */

