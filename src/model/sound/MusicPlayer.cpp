
#include "MusicPlayer.hpp"
MusicPlayer* MusicPlayer::instance = NULL;

void MusicPlayer::deleteInstance() {
    delete instance;
    instance = NULL;
}

MusicPlayer* MusicPlayer::getInstance() {
    if (!MusicPlayer::instance) {
        instance = new MusicPlayer();
    }
    return instance;
}

MusicPlayer::MusicPlayer() {
    currentThread = new QThread();
    moveToThread(currentThread);
    
}

MusicPlayer::~MusicPlayer() {
    stop();
}

void MusicPlayer::start() {
    currentThread->start();
    
    
    
}
void MusicPlayer::restart()
{
    currentThread = new QThread();
    start();
}
void MusicPlayer::stop() {
    // End
    Mix_CloseAudio();
    currentThread->quit();
}
void MusicPlayer::interruptRequest()
{
   // interruptSound=true;
    Mix_HaltMusic();
    std::cout << "Sound interrupted" << std::endl;
}
void MusicPlayer::playSound(QString filepath)
{
    // Init
    if (SDL_Init(SDL_INIT_AUDIO) != 0) {
        std::cerr << "SDL_Init ERROR: " << SDL_GetError() << std::endl;
        return;
    }

    // Open Audio device
    if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048) != 0) {
        std::cerr << "Mix_OpenAudio ERROR: " << Mix_GetError() << std::endl;
        return;
    }
    // Set Volume
    Mix_VolumeMusic(100);

    // Open Audio File
    
    Mix_Music* music = Mix_LoadMUS(filepath.toStdString().c_str());
    
    if (music) {
        // Start Playback
      if (Mix_PlayMusic(music, 1) == 0)
      {
         std::cout << "Sound playing..." << std::endl;
          startTime = SDL_GetTicks();
      }
      else
      {
         std::cerr << "Mix_PlayMusic ERROR: " << Mix_GetError() << std::endl;
        Mix_FreeMusic(music);
        music = 0;
      }
    } else {
        std::cerr << "Mix_LoadMuS ERROR: " << Mix_GetError() << std::endl;
    }
}
