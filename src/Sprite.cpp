#include "../include/Sprite.h"
#include "../include/Resources.h"
#include "../include/Game.h"
#include "../include/Camera.h"

#define CLIP_START_X 0
#define CLIP_START_Y 0

Sprite::Sprite(GameObject &associated) : Component::Component(associated),
                                         scale(Vec2(1, 1)),
                                         timeElapsed(0),
                                         currentFrame(0)
{
    texture = nullptr;
}

Sprite::Sprite(GameObject &associated, std::string file, int frameCount = 1, float frameTime = 1) : Sprite(associated)
{
    Open(file);
    this->frameTime = frameTime;
    this->frameCount = frameCount;
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
    SDL_Rect dstLoc = {int(associated.box.x) + (int)Camera::pos.x, int(associated.box.y) + (int)Camera::pos.y, (int)associated.box.w, (int)associated.box.h};
    // std::cout << "Sprite:  x: " << (int)associated.box.x << std::endl << "y: " << (int)associated.box.y << std::endl << "w: " << clipRect.w << std::endl << "h: " << clipRect.h << std::endl;

    RENDER_ERROR = SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstLoc, associated.angleDeg, nullptr, SDL_FLIP_NONE);
    if (RENDER_ERROR != 0)
    {
        std::cout << "Sprite: Falha ao renderizar a textura: " << SDL_GetError() << std::endl;
    }
}

void Sprite::Render(int x, int y)
{
    int RENDER_ERROR;
    SDL_Rect dstLoc = {x + (int)Camera::pos.x, y + (int)Camera::pos.y, clipRect.w, clipRect.h};

    RENDER_ERROR = SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstLoc, associated.angleDeg, nullptr, SDL_FLIP_NONE);
    if (RENDER_ERROR != 0)
    {
        std::cout << "Sprite: Falha ao renderizar a textura: " << SDL_GetError() << std::endl;
    }
}

int Sprite::GetWidth()
{
    return width * scale.x;
}

int Sprite::GetHeight()
{
    return height * scale.y;
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
    /*
    timeElapsed += dt;
    if (timeElapsed > frameTime)
    {
        SetFrame(frameCount + 1);
    }
    if (currentFrame > numero limite da imagem)
    {
        currentFrame = 0;
    }
    */
}

bool Sprite::Is(std::string type)
{
    return (type == "Sprite");
}

void Sprite::SetScale(float scaleX, float scaleY)
{
    if (scaleX != 0)
    {
        scale.x = scaleX;
        associated.box.w = associated.box.w * scale.x;
    }
    if (scaleX != 0)
    {
        scale.y = scaleY;
        associated.box.h = associated.box.h * scale.y;

    }
}

Vec2 Sprite::GetScale()
{
    return scale;
}

void Sprite::SetFrame(int frame)
{
    /*
        TODO:
            Setar o frame atual
            Setar clip da imagem
    */
}

void Sprite::SetFrameCount(int frameCount)
{
    this->frameCount = frameCount;
    /*
        TODO:
            Resetar o frame inicial para 0
            Recalcular a box do GameObject
    */
}

void Sprite::SetFrameTime(float frameTime)
{
    this->frameTime = frameTime;
}