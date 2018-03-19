
//QT headers
#include <QApplication>
#include <QTimer>

//Other headers
#include <iostream>
#include "keyPressEventHandler.h"
#include "ui/mainWindow.h"

//Controller headers
#include "controller/converseManager.hpp"
#include "controller/faceManager.hpp"
#include "controller/generalManager.hpp"

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
    //cm->startAll();
    
    faceManager* fm = faceManager::getInstance();
    fm->connectToUI(window);
    fm->startAll();
    
    QObject::connect(&app,SIGNAL(aboutToQuit()),generalManager::getInstance(),SLOT(deleteAll()));
    return app.exec();
}
