
#ifndef GENERALMANAGER_HPP
#define GENERALMANAGER_HPP

//Controller headers
#include "converseManager.hpp"
#include "faceManager.hpp"

//Others headers
#include "../keyPressEventHandler.h"
#include "../ui/mainWindow.h"
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
    void connectToUI(mainWindow* ui);
    State state;
    bool onScenario;
    QString nameDetected;
    QString idDetected;

private:
    generalManager();
    static generalManager* instance;

    void deleteTemporaryFiles();
    keyPressEventHandler* eKeyPress;
    mainWindow* ui;
    converseManager* cm;
    faceManager* fm;
public slots:
    void deleteAll();
    void scenarioRecognizedConfirmation(State state, QByteArray data = QByteArray());
    void activateScenarioRecognizedConfirmation(bool val);

signals:
    void newText(QString text);
    void say(QString text);
    void faceRecognitionLog(bool val);

};

#endif /* GENERALMANAGER_HPP */

