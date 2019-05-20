#include "../include/Sprite.h"
#include "../include/Resources.h"
#include "../include/Game.h"
#include "../include/Camera.h"

#define CLIP_START_X 0
#define CLIP_START_Y 0

Sprite::Sprite(GameObject &associated) : Component::Component(associated),
                                         scale(Vec2(1, 1)),
                                         currentFrame(0),
                                         timeElapsed(0)
{
    texture = nullptr;
}

Sprite::Sprite(GameObject &associated, std::string file, int frameCount, float frameTime, float secondsToSelfDestruct) : Sprite(associated)
{
    this->frameTime = frameTime;
    this->frameCount = frameCount;
    this->secondsToSelfDestruct = secondsToSelfDestruct;
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
    SetClip(CLIP_START_X, CLIP_START_Y, width / frameCount, height);
}

void Sprite::SetClip(int x, int y, int w, int h)
{
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;

    associated.box.w = w * scale.x;
    associated.box.h = h * scale.y;
}

void Sprite::Render()
{
    int RENDER_ERROR;
    SDL_Rect dstLoc = {int(associated.box.x) + (int)Camera::pos.x, int(associated.box.y) + (int)Camera::pos.y, (int)(clipRect.w * GetScale().x), (int)(clipRect.h * GetScale().y)};

    RENDER_ERROR = SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstLoc, associated.angleDeg, nullptr, SDL_FLIP_NONE);
    if (RENDER_ERROR != 0)
    {
        std::cout << "Sprite: Falha ao renderizar a textura: " << SDL_GetError() << std::endl;
    }
}

void Sprite::Render(int x, int y)
{
    int RENDER_ERROR;
    SDL_Rect dstLoc = {(int)(x * GetScale().x) + (int)Camera::pos.x, (int)(y * GetScale().y) + (int)Camera::pos.y, (int)(clipRect.w * GetScale().x), (int)(clipRect.h * GetScale().y)};

    RENDER_ERROR = SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstLoc, associated.angleDeg, nullptr, SDL_FLIP_NONE);
    if (RENDER_ERROR != 0)
    {
        std::cout << "Sprite: Falha ao renderizar a textura: " << SDL_GetError() << std::endl;
    }
}

int Sprite::GetWidth()
{   
    int realWidth = (width * scale.x) / frameCount;
    return realWidth;
}

int Sprite::GetHeight()
{
    return height * scale.y;
}

int Sprite::GetWidthNoScale()
{
    int realWidth = width / frameCount;
    return realWidth;
}

int Sprite::GetHeightNoScale()
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
    if (secondsToSelfDestruct > 0)
    {
        selfDestructCount.Update(dt);
        if (selfDestructCount.Get() >= secondsToSelfDestruct)
        {
            associated.RequestDelete();
        }
    }

    timeElapsed += dt;
    if (timeElapsed >= frameTime)
    {
        SetFrame(currentFrame + 1);
    }
    if (currentFrame >= frameCount)
    {
        SetFrame(0);
    }
    
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
        associated.box.w = clipRect.w * scale.x;
    }
    if (scaleX != 0)
    {
        scale.y = scaleY;
        associated.box.h = clipRect.h * scale.y;

    }
}

Vec2 Sprite::GetScale()
{
    return scale;
}

void Sprite::SetFrame(int frame)
{   
    timeElapsed = 0;
    currentFrame = frame;
    SetClip(GetWidthNoScale() * frame, CLIP_START_Y, GetWidthNoScale() , GetHeightNoScale());
}

void Sprite::SetFrameCount(int frameCount)
{
    this->frameCount = frameCount;
    SetFrame(0);
    associated.box.w = GetWidth();
    associated.box.DefineCenter(associated.box.x, associated.box.y);
}

void Sprite::SetFrameTime(float frameTime)
{
    this->frameTime = frameTime;
}

void Sprite::NotifyCollision(GameObject &other)
{}
