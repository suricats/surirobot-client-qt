
#ifndef GENERALMANAGER_HPP
#define GENERALMANAGER_HPP

//Controller headers
#include "converseManager.hpp"
#include "faceManager.hpp"

//Others headers
#include "../keyPressEventHandler.h"
#include <iostream>
#include <string>



class generalManager : public QObject {
    Q_OBJECT
public:
    //Singleton
    static generalManager* getInstance();
    static void deleteInstance();
    //Singleton security
    generalManager(generalManager const&) = delete;
    void operator=(generalManager const&) = delete;

    ~generalManager();
    void configureHandlers(QDialog* ui);

    State state;
    bool onScenario;
    QString nameDetected;
    QString idDetected;

private:
    generalManager();
    static generalManager* instance;

    void deleteTemporaryFiles();
    keyPressEventHandler* eKeyPress;
public slots:
    void deleteAll();
    void scenarioRecognizedConfirmation(State state,QByteArray data);
    void activateScenarioRecognizedConfirmation(bool val);


};

#endif /* GENERALMANAGER_HPP */

