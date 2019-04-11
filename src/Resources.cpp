#include "../include/Resources.h"

std::unordered_map<std::string, SDL_Texture *> Resources::imageTable;
std::unordered_map<std::string, Mix_Music *> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk *> Resources::soundTable;

SDL_Texture *Resources::GetImage(std::string file)
{   
    SDL_Texture* texture;
    std::unordered_map<std::string, SDL_Texture*>::iterator it = Resources::imageTable.find(file);
    if (it == Resources::imageTable.end())
    {   
        // std::cout << (*it) << std::endl;
        std::cout << "Resources: No image found on Table! " << "(" << file << ")"  << std::endl;
        std::cout << "Resources: Loading a new file... " << "(" << file << ")" << std::endl;
        texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
        Resources::imageTable.insert({file, texture});
        std::cout << "Loading done! " << "(" << file << ")" << std::endl;
        return texture;
    }
    
    else
    {
        //std::cout << (*it) << std::endl;
        return it->second;
    }
    
}

void Resources::ClearImages()
{
    /*
    # TODO:
    Percorra a tabela de imagens destruindo textura por textura. Ao final,
    esvazie a tabela. Inclua uma chamada a esse método após o main gameloop, em
    Game::Run.
    */
}

Mix_Music *Resources::GetMusic(std::string file)
{
    /*
    # TODO:
    Usar find e descobrir se a música já existe na tabela de assets.
        * Se sim, retorne o ponteiro gravado lá. 
        * Se não, carregue da mesma forma que fazia em Sprite. Se for carregada com sucesso,
          e insira o par caminho/ponteiro na tabela e retorne o ponteiro.
    */
}
    
void Resources::ClearMusics()
{
    /*
    # TODO:
    Percorra a tabela de imagens destruindo textura por textura. Ao final,
    esvazie a tabela. Inclua uma chamada a esse método após o main gameloop, em
    Game::Run.
    */
}

Mix_Chunk *Resources::GetSound(std::string file)
{
    /*
    # TODO:
    Usar find e descobrir se o som já existe na tabela de assets.
        * Se sim, retorne o ponteiro gravado lá. 
        * Se não, carregue da mesma forma que fazia em Sprite. Se for carregada com sucesso,
          e insira o par caminho/ponteiro na tabela e retorne o ponteiro.
    */
}

void Resources::ClearSounds()
{
    /*
    # TODO:
    Percorra a tabela de imagens destruindo textura por textura. Ao final,
    esvazie a tabela. Inclua uma chamada a esse método após o main gameloop, em
    Game::Run.
    */
}