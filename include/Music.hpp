#include <iostream>
#include <SDL2/SDL.h>


class Music {
    public:
        Music();
        Music(std::string file);
        void Play(int times = -1);
        void Stop(int msToStop = 1500);
        void Open(std::string file);
        bool IsOpen();
    private:
        Mix_Music* music;
}