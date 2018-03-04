
#ifndef FACEMANAGER_HPP
#define FACEMANAGER_HPP

//Model headers
#include "../model/api/EmotionalAPICaller.hpp"
#include "../model/redis/QTRedis.hpp"

//UI headers
#include "../ui/mainWindow.h"

#define EMOTIONAL_URL "https://emotional.api.surirobot.net/emotions/actions/retrieve-facial-emotion"
#define EMOTIONAL_NB_FRAMES 5

class faceManager : public QObject {
    Q_OBJECT
public:
    //Singleton
    static faceManager* getInstance();
    static void deleteInstance();
    //Singleton security
    faceManager(faceManager const&) = delete;
    void operator=(faceManager const&) = delete;
    
    virtual ~faceManager();
    
    void connectToUI(mainWindow* ui);
    void startAll();
    void startFaceRecognition();
    void startEmotionalRecognition();
    void stop();
    
    bool isFaceRecognitionDown();
    bool isEmotionalRecognitionDown();
private:
    EmotionalAPICaller* emotionalWorker;
    QTRedis* faceWorker;
    mainWindow* ui;
    
    faceManager();
    static faceManager* instance;
    
    

};

#endif /* FACEMANAGER_HPP */

