#include "../include/Sprite.h"
#include "../include/Resources.h"
#include "../include/Game.h"

#define CLIP_START_X 0
#define CLIP_START_Y 0

Sprite::Sprite(GameObject &associated) : Component::Component(associated)
{
    texture = nullptr;
}

Sprite::Sprite(GameObject &associated, std::string file) : Sprite(associated)
{
    Open(file);
}

Sprite::~Sprite()
{   
}

void Sprite::Open(std::string file)
{
    texture = Resources::GetImage(file.c_str());
    if (texture == nullptr)
    {
        std::cout << "Sprite: Falha ao carregar a textura " << file << std::endl;
    }
    else
    {
        SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    }
    SetClip(CLIP_START_X, CLIP_START_Y, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h)
{
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;

    associated.box.w = w;
    associated.box.h = h;
}

void Sprite::Render()
{
    int RENDER_ERROR;
    SDL_Rect dstLoc = {int(associated.box.x), int(associated.box.y), clipRect.w, clipRect.h};
    // std::cout << "Sprite:  x: " << (int)associated.box.x << std::endl << "y: " << (int)associated.box.y << std::endl << "w: " << clipRect.w << std::endl << "h: " << clipRect.h << std::endl;


    RENDER_ERROR = SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstLoc);
    if (RENDER_ERROR != 0)
    {
        std::cout << "Sprite: Falha ao renderizar a textura: " << SDL_GetError() << std::endl;
    }
}

void Sprite::Render(int x, int y)
{
    int RENDER_ERROR;
    SDL_Rect dstLoc = {x, y, clipRect.w, clipRect.h};
    // std::cout << "Sprite:  x: " << (int)associated.box.x << std::endl << "y: " << (int)associated.box.y << std::endl << "w: " << clipRect.w << std::endl << "h: " << clipRect.h << std::endl;

    RENDER_ERROR = SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstLoc);
    if (RENDER_ERROR != 0)
    {
        std::cout << "Sprite: Falha ao renderizar a textura: " << SDL_GetError() << std::endl;
    }
}

int Sprite::GetWidth()
{
    return width;
}

int Sprite::GetHeight()
{
    return height;
}

bool Sprite::IsOpen()
{
    std::cout << texture << std::endl;
    if (texture == nullptr)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void Sprite::Update(float dt)
{
}

bool Sprite::Is(std::string type)
{
    if (type == "Sprite")
    {
        return true;
    }
    else
    {
        return false;
    }
}