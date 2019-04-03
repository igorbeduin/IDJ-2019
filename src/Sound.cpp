#include "../include/Sound.h"

Sound::Sound(GameObject &associated) : Component::Component(associated)
{
    chunk = nullptr;
}

Sound::Sound(GameObject &associated, std::string file) : Sound(associated)
{
    Open(file.c_str());
}

Sound::~Sound()
{
    if (chunk != nullptr)
    {
        Stop();
        Mix_FreeChunk(chunk);
    }
}

void Sound::Play(int times)
{
    int loops = times - 1;
    channel = Mix_PlayChannel(-1, chunk, loops);
}

void Sound::Stop()
{
    if (chunk != nullptr)
    {
        Mix_HaltChannel(channel);
    }
}

void Sound::Open(std::string file)
{
    Mix_Chunk *soundERROR;

    soundERROR = Mix_LoadWAV(file.c_str());
    if (soundERROR == NULL)
    {
        std::cout << "Falha ao abrir o som!" << std::endl;
    }
}

void Sound::Update(float dt)
{
}
void Sound::Render()
{
}
bool Is(std::string type)
{
    if (type == "Sound")
    {
        return true;
    }
    else
    {
        return false;
    }
}
