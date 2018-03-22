
#include "faceManager.hpp"

faceManager* faceManager::instance = NULL;

void faceManager::deleteInstance() {
    delete instance;
    instance = NULL;
}

faceManager* faceManager::getInstance() {
    if (!faceManager::instance) {
        instance = new faceManager();
    }
    return instance;
}

faceManager::faceManager() {
    emotionalWorker = new EmotionalAPICaller(EMOTIONAL_URL);
    faceWorker = new QTRedis();
}

faceManager::~faceManager() {

}

void faceManager::connectToUI(mainWindow* ui) {
    this->ui = ui;

    QObject::connect(emotionalWorker,SIGNAL(newReply(QString)),ui,SLOT(setTextDownSignal(QString)));
    QObject::connect(faceWorker, SIGNAL(newPerson(QString,QString)), ui,SLOT(setTextMiddleSignal(QString)));

}

void faceManager::startAll() {
   startEmotionalRecognition();
   startFaceRecognition();
}

void faceManager::startFaceRecognition() {
    faceWorker->start();
}

void faceManager::startEmotionalRecognition() {
    emotionalWorker->start();
}
void faceManager::stop()
{
    emotionalWorker->stop();
    faceWorker->currentThread->quit();
}
bool faceManager::isFaceRecognitionDown() {
    return false;
}

bool faceManager::isEmotionalRecognitionDown() {
    return false;
}