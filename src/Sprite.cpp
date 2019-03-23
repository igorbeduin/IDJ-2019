#include "Sprite.hpp"


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
    texture = IMG_LoadTexture(renderer, path); // Renderer deve ser o renderer do Game
    if (IMG_LoadTexture(renderer, path) == nullptr) {
        std::cout << "Deu bosta";
    } 
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect = {x, y, w, h};
}

void Sprite::Render(int x, int y) {
    SDL_Rect* dstLoc = {x, y, clipRect.w, clipRect.h};
    SDL_RenderCopy(renderer, texture, clipRect, dstLoc);
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
