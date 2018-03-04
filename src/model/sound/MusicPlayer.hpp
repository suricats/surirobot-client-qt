
#ifndef MUSICPLAYER_HPP
#define MUSICPLAYER_HPP

#include <QThread>
#include <string>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
class MusicPlayer : public QObject {
    Q_OBJECT
public:
    QThread* currentThread;
    MusicPlayer();
    virtual ~MusicPlayer();
    void start();
    void stop();
    void restart();
public slots:
    void playSound(QString filepath);


};

#endif /* MUSICPLAYER_HPP */

