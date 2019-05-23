#include "../include/Text.h"
#include "../include/Game.h"

Text::Text(GameObject& associated, std::string fontFile, int fontSize, 
           TextStyle style, std::string text, SDL_Color color) : Component::Component(associated),
                                                                 text(text),
                                                                 style(style),
                                                                 fontSize(fontSize),
                                                                 fontFile(fontFile),
                                                                 color(color),
                                                                 texture(nullptr)
                                                                 font(nullptr)
{
    // Iniciar font com os atributos recebidos
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
{}

void Text::Render()
{
    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, /*srcrect*/, /*dstrect*/, associated.angleDeg, nullptr, SDL_FLIP_NONE);
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

    // TODO: Carregar nova fonte
    // TODO: Termianr RemakeTexture

}