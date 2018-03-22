
#ifndef FACEMANAGER_HPP
#define FACEMANAGER_HPP

//Model headers
#include "../model/api/EmotionalAPICaller.hpp"
#include "../model/redis/QTRedis.hpp"

//UI headers
#include "../ui/mainWindow.h"

#define EMOTIONAL_URL "http://ec2-54-212-240-38.us-west-2.compute.amazonaws.com:8080/emotions/actions/retrieve-video-emotion"
#define EMOTIONAL_NB_FRAMES 5
#define EMOTIONAL_IMAGE_SIZE 200 //in pixels
#define EMOTIONAL_DELAY 4000 //in ms



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
    QTRedis* faceWorker;
private:
    EmotionalAPICaller* emotionalWorker;
    
    mainWindow* ui;

    faceManager();
    static faceManager* instance;
};

#endif /* FACEMANAGER_HPP */

