#include "../include/Sprite.h"
#include "../include/Game.h"

#define CLIP_START_X 0
#define CLIP_START_Y 0

Sprite::Sprite() {
    texture = nullptr;
}

Sprite::Sprite(std::string file) {
    texture = nullptr;
    Open(file);
}

Sprite::~Sprite(){
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    };
}

void Sprite::Open(std::string file) {
    if (texture != nullptr) {
       SDL_DestroyTexture(texture);
    };
    texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    if (texture == nullptr)
    {
        std::cout << "Falha ao carregar a textura" << std::endl;
    } else {
        std::cout << "Textura carregada com sucesso!" << std::endl;
        SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    }
    SetClip(CLIP_START_X, CLIP_START_Y, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render(int x, int y) {
    int RENDER_ERROR;
    SDL_Rect dstLoc = {x, y, GetWidth(), GetHeight()};

    RENDER_ERROR = SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstLoc);
    if (RENDER_ERROR != 0) {
        std::cout << "Falha ao renderizar a textura: " << SDL_GetError() << std::endl;
    }
}

int Sprite::GetWidth() {
    return width;
}

int Sprite::GetHeight() {
    return height;
}

bool Sprite::IsOpen() {
    std::cout << texture << std::endl;
    if (texture == nullptr) {
        return false;
    } else {
        return true;
    }
}
