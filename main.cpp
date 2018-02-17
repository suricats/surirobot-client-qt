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
#include <qnetwork.h>
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
//#include "connectors/redis/QTRedis.hpp"

int main(int argc, char *argv[]) {
    std::cout << "Program started.  " << std::endl;

    QApplication app(argc, argv);
    mainWindow* window = new mainWindow();

    //Image
    QImage imageNormal;
    imageNormal.load("./img/Surirobot1.png");
    window->setImage(imageNormal);

    //Text
    QFont f("Roboto", 40, QFont::Bold);
    window->setTextFont(f);
    window->setText("Salut !");

    //EditText
    window->setEditText();
    //window->show();
    window->smartShow();
    window->updateWidgets();


    
    
    APICaller* APIworker = new APICaller;
    QThread* APIThread = new QThread;
    APIworker->set(APIThread);
    QObject::connect(APIworker, SIGNAL(messageChanged(QString)), window, SLOT(changeText(QString)));
    APIThread->start();
    
    //Timer
    QTimer* activeTimer = new QTimer(window);
    activeTimer->setInterval(5*1000);
    //activeTimer->setSingleShot(true);
    QObject::connect(activeTimer, SIGNAL(timeout()), window, SLOT(sendEditText()));
    QObject::connect(window,SIGNAL(sendEditText_signal(QString)),APIworker,SLOT(sendRequest(QString)));
    activeTimer->start();
    /*
    QTRedis redis;
    redis.run();
    QObject::connect(&redis, &QTRedis::signalNewPerson, window, &mainWindow::changeText);
     */
    return app.exec();


}
