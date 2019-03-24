#include "../include/Sprite.hpp"
#include "../include/Game.hpp"


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
    Game& game = Game::GetInstance();  // Singleton's instance for local use

    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    };
    texture = IMG_LoadTexture(game.GetRenderer(), file.c_str());
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render(int x, int y) {
    Game& game = Game::GetInstance(); // Singleton's instance for local use
    SDL_Rect dstLoc = {x, y, clipRect.w, clipRect.h};

    SDL_RenderCopy(game.GetRenderer(), texture, &clipRect, &dstLoc);
}

int Sprite::GetWidth() {
    return width;
}

int Sprite::GetHeight() {
    return height;
}

bool Sprite::IsOpen() {
    if (texture != nullptr) {
        return true;
    } else {
        return false;
    }
}
