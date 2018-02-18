/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

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

#include "APICaller.h"
#include "connectors/redis/QTRedis.hpp"

int main(int argc, char *argv[]) {
    std::cout << "Program started.  " << std::endl;

    QApplication app(argc, argv);
    mainWindow* window = new mainWindow();

    //Image
    QImage imageNormal;
    imageNormal.load("./img/SuriRobot1.png");
    window->setImage(imageNormal);

    //Text
    QFont f("Roboto", 40, QFont::Bold);
    window->setTextFont(f);
    window->setText("Salut !");

    //EditText
    window->setEditText();
    
    
    //Show
    window->smartShow();

        
    //Timer dispaly fixer
    QTimer* displayFixer = new QTimer(window);
    displayFixer->setInterval(100);
    displayFixer->setSingleShot(true);
    QObject::connect(displayFixer, SIGNAL(timeout()), window, SLOT(updateSlot()));
    displayFixer->start();
    
    APICaller* APIworker = new APICaller;
    QThread* APIThread = new QThread;
    APIworker->set(APIThread);
    QObject::connect(APIworker, SIGNAL(messageChanged(QString)), window, SLOT(changeText(QString)));
    APIThread->start();
    
    //Timer for test
    QTimer* activeTimer = new QTimer(window);
    activeTimer->setInterval(5*1000);
    QObject::connect(activeTimer, SIGNAL(timeout()), window, SLOT(sendEditText()));
    QObject::connect(window,SIGNAL(sendEditText_signal(QString)),APIworker,SLOT(sendRequest(QString)));
    activeTimer->start();
    
    //Redis for face recognition
    QTRedis* redis = new QTRedis();
    redis->run();
    QObject::connect(redis, &QTRedis::signalNewPerson, window, &mainWindow::changeText);
     
    return app.exec();


}
