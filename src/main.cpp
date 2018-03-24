
//QT headers
#include <QApplication>
#include <QTimer>

//Other headers
#include <iostream>
#include "keyPressEventHandler.h"
#include "ui/mainWindow.h"
#include "conf.hpp"
//Controller headers
#include "controller/converseManager.hpp"
#include "controller/faceManager.hpp"
#include "controller/generalManager.hpp"

int main(int argc, char *argv[]) {
    std::cout << "Program started.  " << std::endl;
    //qputenv("QT_DEBUG_PLUGINS", QByteArray("1"));
    qRegisterMetaType<State>("State");
    QApplication app(argc, argv);
    mainWindow* window = new mainWindow();
    
    generalManager* gm = generalManager::getInstance();
    gm->configureHandlers(window);
    gm->connectToUI(window);
    
    //EditText
    //window->setEditText();
    //Show
    window->smartShow();
    
    converseManager* cm = converseManager::getInstance();
    cm->setAudioPeriod(4);
    cm->startAll();
    
    faceManager* fm = faceManager::getInstance();
    fm->startFaceRecognition();
    
    QObject::connect(&app,SIGNAL(aboutToQuit()),gm,SLOT(deleteAll()));
    return app.exec();
}
