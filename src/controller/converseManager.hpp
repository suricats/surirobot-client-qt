
#ifndef CONVERSEMANAGER_HPP
#define CONVERSEMANAGER_HPP

//Model headers
#include "../model/api/ConverseAPICaller.hpp"
#include "../model/api/EmotionalAPICaller.hpp"
#include "../model/api/NLPAPICaller.hpp"
#include "../model/sound/SpeechRecording.hpp"
#include "../model/api/TTSAPICaller.hpp"
//UI headers
#include "../ui/mainWindow.h"


#define NLP_URL "https://nlp.api.surirobot.net/getanswer"
#define CONVERSE_URL "https://converse.api.surirobot.net/converse"
#define TTS_URL "https://text-to-speech.api.surirobot.net/speak"
//#define CONVERSE_URL "http://localhost:6900/converse"
#define NLP_INTERVAL_REQUEST 4 //in seconds

class converseManager : public QObject {
    Q_OBJECT
public:
    //Singleton
    static converseManager* getInstance();
    static void deleteInstance();
    //Singleton security
    converseManager(converseManager const&) = delete;
    void operator=(converseManager const&) = delete;

    virtual ~converseManager();
    void connectToUI(mainWindow* ui);
    void startAll();
    void startNLP();
    void startConverse();
    void startTTS();
    void stop();
    bool isNLPDown();
    bool isConverseDown();
    void debugNLP(bool set = true);
    
    int getAudioPeriod();
    void setAudioPeriod(int nb);
    
    SpeechRecording* getAudioRecorder();
    
    ConverseAPICaller* converseWorker;
    SpeechRecording* audioRecorder;
    TTSAPICaller* speechWorker;
private:
    QTimer* debugTimer;
    mainWindow* ui;
    NLPAPICaller* nlpWorker;
    
    
    bool nlpDebug;

    converseManager();
    static converseManager* instance;
public slots:
    
};

#endif /* CONVERSEMANAGER_HPP */

