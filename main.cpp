/*
 * File:   main.cpp
 * Author: Thomas
 *
 * Created on 10 octobre 2017, 22:28
 */

#include <QApplication>
#include <QImage>
#include <QtWidgets/QLabel>
#include <QGridLayout>
#include <QRect>
#include <QDesktopWidget>
#include <iostream>
#include <string>
#include <unistd.h>
#include <QtWidgets/qlayout.h>
#include "keyPressEventHandler.h"
#include "mainWindow.h"
#include <QtNetwork>
#include <QNetworkReply>
#include <QTimer>
#include <QtMultimedia/QtMultimedia>
#include <QtMultimedia/QCamera>
#include <QtMultimedia/QCameraInfo>

#include "ConverseAPICaller.h"
#include "connectors/redis/QTRedis.hpp"
#include "EmotionalAPICaller.h"

int main(int argc, char *argv[]) {
    std::cout << "Program started.  " << std::endl;
    
    QApplication app(argc, argv);
    std::cout << "Hey";
    mainWindow* window = new mainWindow();
    if(QCameraInfo::availableCameras().count() <= 0) window->setTextDown("No available camera.");
        
    //Image
    QImage imageNormal;
    imageNormal.load("./img/SuriRobot1.png");
    window->setImage(imageNormal);

   
    //Camera
    
    //EditText
    window->setEditText();
    
    //Show
    window->smartShow();
    
    //Converse API
    ConverseAPICaller* converseWorker = new ConverseAPICaller();
    QObject::connect(converseWorker, SIGNAL(messageChanged(QString)), window, SLOT(setTextUpSignal(QString)));
    converseWorker->start();
    
    //Emotional API
    EmotionalAPICaller* emotionalWorker = new EmotionalAPICaller();
    QObject::connect(emotionalWorker,SIGNAL(messageChanged(QString)),window,SLOT(setTextDownSignal(QString)));
    emotionalWorker->start();
    
    //Timer for test
    QTimer* activeTimer = new QTimer(window);
    activeTimer->setInterval(5*1000);
    QObject::connect(activeTimer, SIGNAL(timeout()), window, SLOT(sendEditText()));
    QObject::connect(window,SIGNAL(sendEditTextSignal(QString)),converseWorker,SLOT(sendRequest(QString)));
    //QObject::connect(window,SIGNAL(sendEditTextSignal(QString)),emotionalWorker,SLOT(sendRequest(QString)));
    activeTimer->start();
    
    
    
    //Redis for face recognition
    QTRedis* redis = new QTRedis();
    redis->start();
    QObject::connect(redis, &QTRedis::signalNewPerson, window, &mainWindow::setTextMiddleSignal);
     
    return app.exec();


}
