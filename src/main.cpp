
//QT includes
#include <QApplication>
#include <QTimer>
#include <QtMultimedia/QtMultimedia>
#include <QtMultimedia/QCamera>

//Other includes    
#include <iostream>
#include "keyPressEventHandler.h"
#include "ui/mainWindow.h"
#include "api/ConverseAPICaller.hpp"
#include "api/EmotionalAPICaller.hpp"
#include "redis/QTRedis.hpp"

int main(int argc, char *argv[]) {
    std::cout << "Program started.  " << std::endl;
    
    QApplication app(argc, argv);
    mainWindow* window = new mainWindow();
    
    if(QCameraInfo::availableCameras().count() <= 0) window->setTextDown("No available camera.");
    
    //Image
    QImage imageNormal;
    imageNormal.load("res/SuriRobot1.png");
    window->setImage(imageNormal);

   
    //Camera
    //EditText
    window->setEditText();
    
    //Show
    window->smartShow();
    
    //Converse API
    APICaller* converseWorker = new ConverseAPICaller("https://nlp.api.surirobot.net/getanswer");
    QObject::connect(converseWorker, SIGNAL(newReply(QString)), window, SLOT(setTextUpSignal(QString)));
    converseWorker->start();
    
    //Emotional API
    APICaller* emotionalWorker = new EmotionalAPICaller("https://emotional.api.surirobot.net");
    QObject::connect(emotionalWorker,SIGNAL(newReply(QString)),window,SLOT(setTextDownSignal(QString)));
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
