
#include "MusicPlayer.hpp"

MusicPlayer::MusicPlayer() {
    currentThread = new QThread();
    moveToThread(currentThread);
    
}

MusicPlayer::~MusicPlayer() {
    stop();
}

void MusicPlayer::start() {
    currentThread->start();
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
void MusicPlayer::playSound(QString filepath)
{
    // Set Volume
    Mix_VolumeMusic(100);

    // Open Audio File
    Mix_Music* music = Mix_LoadMUS(filepath.toStdString().c_str());
    
    if (music) {
        // Start Playback
      if (Mix_PlayMusic(music, 1) == 0)
      {
         unsigned int startTime = SDL_GetTicks();

         // Wait
         while (Mix_PlayingMusic())
         {
            SDL_Delay(10000);
            std::cout << "Time: " << (SDL_GetTicks() - startTime) / 1000 << std::endl;
         }
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