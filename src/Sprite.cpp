#include "../include/Sprite.h"
#include "../include/Game.h"
#include "../include/GameObject.h"

#define CLIP_START_X 0
#define CLIP_START_Y 0

Sprite::Sprite(std::string file) : Component::Component(associated)
{
    Open(file);
}

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
    if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
    };
}

void Sprite::Open(std::string file)
{
    if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
    };
    texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    if (texture == nullptr)
    {
        std::cout << "Falha ao carregar a textura" << std::endl;
    }
    else
    {
        std::cout << "Textura carregada com sucesso!" << std::endl;
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
}

void Sprite::Render()
{
    int RENDER_ERROR;
    SDL_Rect dstLoc = {int(associated.box.x), int(associated.box.y), int(associated.box.w), int(associated.box.h)};

    RENDER_ERROR = SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstLoc);
    if (RENDER_ERROR != 0)
    {
        std::cout << "Falha ao renderizar a textura: " << SDL_GetError() << std::endl;
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