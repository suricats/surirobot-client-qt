
#include "converseManager.hpp"
converseManager* converseManager::instance = NULL;

void converseManager::deleteInstance() {
    delete instance;
    instance = NULL;
}

converseManager* converseManager::getInstance() {
    if (!converseManager::instance) {
        instance = new converseManager();
    }

    return instance;
}

converseManager::converseManager() {
    debugTimer = new QTimer();
    debugTimer->setInterval(NLP_INTERVAL_REQUEST * 1000);
    audioRecorder = new SpeechRecording;
    nlpWorker = new NLPAPICaller(NLP_URL);
    converseWorker = new ConverseAPICaller(CONVERSE_URL);
    QObject::connect(audioRecorder, SIGNAL(newSoundCreated(QString)), converseWorker, SLOT(sendRequest(QString)));
    nlpDebug = false;
}

converseManager::~converseManager() {
    delete audioRecorder;
    delete nlpWorker;
    delete converseWorker;
}

void converseManager::connectToUI(mainWindow* ui) {
    this->ui = ui;

    QObject::connect(converseWorker, SIGNAL(newReply(QString)), ui, SLOT(setTextUpSignal(QString)));
    QObject::connect(nlpWorker, SIGNAL(newReply(QString)), ui, SLOT(setTextUpSignal(QString)));
    QObject::connect(ui->MicButton, SIGNAL(released()), audioRecorder, SLOT(recordPSeconds()));

    QObject::connect(debugTimer, SIGNAL(timeout()), ui, SLOT(sendEditText()));
}

void converseManager::startConverse() {
    converseWorker->start();
    audioRecorder->start();
}

void converseManager::startNLP() {
    nlpWorker->start();
}

void converseManager::startAll() {
    startConverse();
    startNLP();
}
void converseManager::stop()
{
    nlpWorker->stop();
    converseWorker->stop();
    debugTimer->stop();
    audioRecorder->currentThread->quit();
}

void converseManager::debugNLP(bool set) {
    if (nlpDebug == set)return;
    if (set) {
        nlpDebug = true;
        debugTimer->start();
        //TO DO : show debug interface
    } else {
        nlpDebug = false;
        debugTimer->stop();
        //TO DO : hide debug interface
    }
}

bool converseManager::isConverseDown() {
    return false;
}

bool converseManager::isNLPDown() {
    return false;
}

int converseManager::getAudioPeriod() {
    return audioRecorder->audioPeriod;
}

void converseManager::setAudioPeriod(int nb) {
    if(nb>0)audioRecorder->audioPeriod=nb;
    else std::cerr << "Invalid audio period." << std::endl;
    
}


