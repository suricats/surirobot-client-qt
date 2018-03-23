#include "generalManager.hpp"

generalManager* generalManager::instance = NULL;

void generalManager::deleteInstance() {
    delete instance;
    instance = NULL;
}

generalManager* generalManager::getInstance() {
    if (!generalManager::instance) {
        instance = new generalManager();
    }
    return instance;
}

generalManager::generalManager() {
    eKeyPress = new keyPressEventHandler();
    state = STATE_IDLE;
    onScenario = false;
    cm = converseManager::getInstance();
    fm = faceManager::getInstance();
    QObject::connect(fm->faceWorker, SIGNAL(activateDetectionScenario(State, QByteArray)), this, SLOT(scenarioRecognizedConfirmation(State, QByteArray)));
    QObject::connect(this, SIGNAL(say(QString)), cm->speechWorker, SLOT(sendRequest(QString)));
    QObject::connect(this, SIGNAL(void faceRecognitionLog(QString,bool)), fm->faceAPIworker, SLOT(sendLog(QString,bool)));

}

generalManager::~generalManager() {

}

void generalManager::configureHandlers(QDialog* ui) {
    ui->installEventFilter(eKeyPress);
}

void generalManager::deleteAll() {
    //Stop the controllers
    fm->stop();
    cm->stop();
    //Delete the controllers
    faceManager::deleteInstance();
    converseManager::deleteInstance();
    deleteTemporaryFiles();

}

void generalManager::deleteTemporaryFiles() {
    QString path = TMP_DIR;
    QDir dir(path);
    dir.setNameFilters(QStringList() << "*.*");
    dir.setFilter(QDir::Files);

    foreach(QString dirFile, dir.entryList()) {
        dir.remove(dirFile);
    }
}

void generalManager::scenarioRecognizedConfirmation(State newState, QByteArray data) {

    if (state != newState) {
        state = newState;
        switch (newState) {
            case State::STATE_IDLE:
            {
                std::cout << "STATE IDLE" << std::endl;
                cm->converseWorker->intentMode = false;
                QObject::disconnect(cm->converseWorker, SIGNAL(newIntent(State, QByteArray)), this, SLOT(scenarioRecognizedConfirmation(State, QByteArray)));
                
            }
                break;
            case State::STATE_DETECTED:
            {
                std::cout << "STATE DETECTED" << std::endl;
                cm->converseWorker->intentMode = true;

                QObject::connect(cm->converseWorker, SIGNAL(newIntent(State, QByteArray)), this, SLOT(scenarioRecognizedConfirmation(State, QByteArray)));
                std::string message = data.toStdString();
                std::string delimiter = ".";

                size_t pos = message.find(delimiter);
                idDetected = QString::fromStdString(message.substr(0, pos));
                nameDetected = QString::fromStdString(message.substr(pos + delimiter.length(), message.length()));

                QString text("Oh ! Salut " + nameDetected + " ! Est ce que c'est bien toi ?");
                emit newText(text);
                emit say(text);
            }
                break;
            case State::STATE_NOT_DETECTED:
            {
                QString text("Au revoir " + nameDetected + ".");
                emit newText(text);
                emit say(text);
                scenarioRecognizedConfirmation(State::STATE_IDLE);
            }
                break;
            case State::STATE_WAITING_FOR_CONFIRMATION:
                break;
            case State::STATE_CONFIRMATION_YES:
            {
                std::cout << "STATE YES" << std::endl;
                QString text("Parfait ! Chattons ensemble à présent :)");
                emit newText(text);
                emit say(text);
                emit faceRecognitionLog(idDetected,true);
                scenarioRecognizedConfirmation(State::STATE_IDLE);
            }
                break;
            case State::STATE_CONFIRMATION_NO:
            {
                std::cout << "STATE NO" << std::endl;
                QString text("Oh mince je me suis trompé. J'essayerai de faire mieux la prochaine fois !");
                emit newText(text);
                emit say(text);
                emit faceRecognitionLog(idDetected,false);
                scenarioRecognizedConfirmation(State::STATE_IDLE);
            }
                break;

        }
    }

}

void generalManager::connectToUI(mainWindow* ui) {
    this->ui = ui;
    cm->connectToUI(ui);
    fm->connectToUI(ui);

    QObject::connect(this, SIGNAL(newText(QString)), ui, SLOT(setTextMiddleSignal(QString)));

}

void generalManager::activateScenarioRecognizedConfirmation(bool val) {
    if (val != onScenario) {
        onScenario = val;
        eKeyPress->onScenario = val;
    }
}