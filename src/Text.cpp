#include "../include/Text.h"
#include "../include/Game.h"
#include "../include/Camera.h"
#include "../include/Resources.h"

Text::Text(GameObject& associated, std::string fontFile, int fontSize, 
           TextStyle style, std::string text, SDL_Color color, int blinkPeriod) : Component::Component(associated),
                                                                                  font(nullptr),
                                                                                  texture(nullptr),
                                                                                  text(text),
                                                                                  style(style),
                                                                                  fontFile(fontFile.c_str()),
                                                                                  fontSize(fontSize),
                                                                                  color(color),
                                                                                  blinkPeriod(blinkPeriod)
                {
    font = TTF_OpenFont(fontFile.c_str(), fontSize);
    RemakeTexture();
}

Text::~Text()
{
    if (texture != nullptr)
    {
        texture = nullptr;
    }
}

void Text::Update(float dt)
{   
    if (blinkTimer.Get() < blinkPeriod)
    {
        blinkTimer.Update(dt);
    }
    else
    {
        blinkTimer.Restart();
    }
}

void Text::Render()
{   
    if (blinkTimer.Get() <= blinkPeriod / 2)
    {
        int RENDER_ERROR;
        SDL_Rect clipRect = {0, 0, (int)associated.box.w, (int)associated.box.h};

        SDL_Rect dst = {(int)associated.box.x + (int)Camera::pos.x, 
                        (int)associated.box.y + (int)Camera::pos.y, 
                        clipRect.w, 
                        clipRect.h};

        std::cout << "associated.box.x: " << associated.box.x << std::endl;
        std::cout << "associated.box.y: " << associated.box.y << std::endl;

        std::cout << "dst.x: " << dst.x << std::endl;
        std::cout << "dst.y: " << dst.y << std::endl;

        RENDER_ERROR = SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dst, associated.angleDeg, nullptr, SDL_FLIP_NONE);
        if (RENDER_ERROR != 0)
        {
            std::cout << "Text: Falha ao renderizar a textura: " << SDL_GetError() << std::endl;
        }
    }
}

void Text::SetText(std::string text)
{
    this->text = text;
    RemakeTexture();
}

void Text::SetColor(SDL_Color color)
{
    this->color = color;
    RemakeTexture();
}

void Text::SetStyle(TextStyle style)
{
    this->style = style;
    RemakeTexture();
}

void Text::SetFontSize(int fontSize)
{
    this->fontSize = fontSize;
    RemakeTexture();
}

void Text::RemakeTexture()
{
    if (texture != nullptr)
    {
        texture = nullptr;
    }

    font = Resources::GetFont(fontFile, fontSize);
    if (font == NULL)
    {
        std::cout << "Text: Falha ao obter a fonte: " << SDL_GetError() << std::endl;
    }
    SDL_Surface *temp_surface;

    switch (style)
    {
        case SOLID:
        {
            temp_surface = TTF_RenderText_Solid(font, text.c_str(), color);

            break;

        }
        case SHADED:
        {
            temp_surface = TTF_RenderText_Shaded(font, text.c_str(), color, BACKGROUND_COLOR);

            break;
        }
        case BLENDED:
        {
            temp_surface = TTF_RenderText_Blended(font, text.c_str(), color);

            break;
        }
    }
    int tempWidth, tempHeight;
    texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), temp_surface);
    SDL_QueryTexture(texture, nullptr, nullptr, &tempWidth, &tempHeight);

    associated.box.w = tempWidth;
    associated.box.h = tempHeight;
    SDL_FreeSurface(temp_surface);
}

bool Text::Is(std::string type)
{
    return (type == "Text");
}