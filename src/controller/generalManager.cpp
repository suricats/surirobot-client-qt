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
    QObject::connect(faceManager::getInstance()->faceWorker, SIGNAL(activateDetectionScenario(State, QByteArray)), this, SLOT(scenarioRecognizedConfirmation(State, QByteArray)));

}

generalManager::~generalManager() {

}

void generalManager::configureHandlers(QDialog* ui) {
    ui->installEventFilter(eKeyPress);
}

void generalManager::deleteAll() {
    //Stop the controllers
    faceManager::getInstance()->stop();
    converseManager::getInstance()->stop();
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
                std::cout << "STATE IDLE" << std::endl;
                converseManager::getInstance()->converseWorker->intentMode = false;
                QObject::disconnect(converseManager::getInstance()->converseWorker, SIGNAL(newIntent(State, QByteArray)), this, SLOT(scenarioRecognizedConfirmation(State, QByteArray)));
                break;
            case State::STATE_DETECTED:
            {
                std::cout << "STATE DETECTED" << std::endl;
                converseManager::getInstance()->converseWorker->intentMode = true;
                QObject::connect(converseManager::getInstance()->converseWorker, SIGNAL(newIntent(State, QByteArray)), this, SLOT(scenarioRecognizedConfirmation(State, QByteArray)));
                std::string message = data.toStdString();
                std::string delimiter = ".";

                size_t pos = message.find(delimiter);
                idDetected = QString::fromStdString(message.substr(0, pos));
                nameDetected = QString::fromStdString(message.substr(pos + delimiter.length(), message.length()));
            }
                break;
            case State::STATE_WAITING_FOR_CONFIRMATION:
                break;
            case State::STATE_CONFIRMATION_YES:
                std::cout << "OUI" << std::endl;
                scenarioRecognizedConfirmation(State::STATE_IDLE, QByteArray());
                break;
            case State::STATE_CONFIRMATION_NO:
                std::cout << "NON" << std::endl;
                scenarioRecognizedConfirmation(State::STATE_IDLE, QByteArray());
                break;

        }
    }

}

void generalManager::activateScenarioRecognizedConfirmation(bool val) {
    if (val != onScenario) {
        onScenario = val;
        eKeyPress->onScenario = val;
    }
}