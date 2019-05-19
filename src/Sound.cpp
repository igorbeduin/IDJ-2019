#include "../include/Sound.h"
#include "../include/Resources.h"

Sound::Sound(GameObject &associated) : Component::Component(associated)
{
    chunk = NULL;
}

Sound::Sound(GameObject &associated, std::string file) : Sound(associated)
{
    Open(file.c_str());
}

Sound::~Sound()
{

}

void Sound::Play(int times)
{
    int loops = times - 1;
    channel = Mix_PlayChannel(-1, chunk, loops);
    if (channel == -1)
    {
        std::cout << "Sound: Falha ao tocar o som!" << SDL_GetError() << std::endl;
    }
}

void Sound::Stop()
{
    if (chunk != NULL)
    {
        Mix_HaltChannel(channel);
    }
}

void Sound::Open(std::string file)
{   
    chunk = Resources::GetSound(file.c_str());
    // chunk = Mix_LoadWAV(file.c_str());
    if (chunk == NULL)
    {
        std::cout << "Sound: Falha ao abrir o som!" << std::endl;
    } 
  
}

void Sound::Update(float dt)
{
}
void Sound::Render()
{
}
bool Sound::Is(std::string type)
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

void Sound::NotifyCollision(GameObject &other)
{}
