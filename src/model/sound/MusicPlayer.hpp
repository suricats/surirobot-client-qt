
#ifndef MUSICPLAYER_HPP
#define MUSICPLAYER_HPP

#include <QThread>
#include <string>
#include <iostream>
#include <cstring>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class MusicPlayer : public QObject {
    Q_OBJECT
public:
    //Singleton
    static MusicPlayer* getInstance();
    static void deleteInstance();
    //Singleton security
    MusicPlayer(MusicPlayer const&) = delete;
    void operator=(MusicPlayer const&) = delete;
    
    QThread* currentThread;
    
    virtual ~MusicPlayer();
    void start();
    void stop();
    void restart();
public slots:
    void playSound(QString filepath);
    void interruptRequest();

private:
    MusicPlayer();
    static MusicPlayer* instance;
    unsigned int startTime;


};

#endif /* MUSICPLAYER_HPP */

