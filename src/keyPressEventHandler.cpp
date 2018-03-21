
#include "keyPressEventHandler.h"

keyPressEventHandler::keyPressEventHandler() {
    cm = converseManager::getInstance();
    sr = cm->getAudioRecorder();
    expirationTimer = new QTimer();
    expirationTimer->setInterval(500);
    expirationTimer->setSingleShot(true);
    QObject::connect(expirationTimer,SIGNAL(timeout()),sr,SLOT(saveBuffer()));
    QObject::connect(sr,SIGNAL(isRecording(bool)),this,SLOT(manageRecord(bool)));
    QObject::connect(this,SIGNAL(startRecord()),sr,SLOT(recordInBuffer()));
    audioRecording=false;
    
    
}

keyPressEventHandler::~keyPressEventHandler() {
}
//Communication between 2 different threads
void keyPressEventHandler::manageRecord(bool val)
{
    audioRecording=val;
}
bool keyPressEventHandler::eventFilter(QObject* obj, QEvent* event) {
    
    //Key pressed
    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent* keyP = static_cast<QKeyEvent*> (event);
        if(keyP->key() == Qt::Key_Escape || keyP->key() == Qt::Key_Return) QApplication::quit();
        else if(keyP->key() == Qt::Key_C)
        {
            //Expiration timer is set to prevent keyboard error
            if(expirationTimer->isActive())expirationTimer->stop();
            if(!audioRecording)
            {
                emit startRecord();
                
            }
            return true;
        }
        else return QObject::eventFilter(obj, event);
    }
    //Key released
    else if(event->type() == QEvent::KeyRelease)
    {
        QKeyEvent* keyR = static_cast<QKeyEvent*> (event);
        if(keyR->key() == Qt::Key_C && !expirationTimer->isActive())
        {
            expirationTimer->start();
            return true;
        }
    }
    return QObject::eventFilter(obj, event);
    
}