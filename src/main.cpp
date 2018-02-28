
//QT headers
#include <QApplication>
#include <QTimer>

//Other headers    
#include <iostream>
#include "keyPressEventHandler.h"
#include "ui/mainWindow.h"

//Controller headers
#include "controller/converseManager.hpp"

//UI headers
#include "model/api/EmotionalAPICaller.hpp"
#include "model/redis/QTRedis.hpp"

int main(int argc, char *argv[]) {
    std::cout << "Program started.  " << std::endl;
    //qputenv("QT_DEBUG_PLUGINS", QByteArray("1"));
    
    QApplication app(argc, argv);
    
    mainWindow* window = new mainWindow();
    
    
    //EditText
    window->setEditText();
    
    //Show
    window->smartShow();
    
    converseManager* cm = converseManager::getInstance();
    cm->connectToUI(window);
    cm->setAudioPeriod(4);
    cm->startAll();
    
    ///TO DO : create a file downloader as APICaller child
    ///TO DO : implement faceManager
    //Emotional API
    //APICaller* emotionalWorker = new EmotionalAPICaller("https://emotional.api.surirobot.net/emotions/actions/retrieve-facial-emotion");
    //QObject::connect(emotionalWorker,SIGNAL(newReply(QString)),window,SLOT(setTextDownSignal(QString)));
    //emotionalWorker->start();
    
    
    //Redis for face recognition
    QTRedis* redis = new QTRedis();
    redis->start();
    QObject::connect(redis, &QTRedis::signalNewPerson, window, &mainWindow::setTextMiddleSignal);
    
    
    QObject::connect(&app,SIGNAL(aboutToQuit()),cm,SLOT(deleteAudioFiles()));
    //TO DO : had a way to delete singlotons here
    return app.exec();


}
