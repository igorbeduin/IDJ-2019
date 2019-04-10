#include "../include/TileMap.h"

TileMap::TileMap(GameObject &associated, std::string file, TileSet *tileSet) : Component::Component(associated),
                                                                               tileSet(tileSet)
{
    TileMap::Load(file.c_str());
}

void TileMap::Load(std::string file)
{
    int tile;
    char separator;
    std::ifstream file_object;
    file_object.open(file.c_str());
    // Garante que o arquivo foi aberto corretamente
    if (file_object) 
    {
        // Pega os três primeiros valores do arquivo tileMap.txt
        file_object >> mapWidth >> separator >> mapHeight >> separator >> mapDepth >> separator;
        std::cout << "tileMap width: " << mapWidth << std::endl  << "tileMap height: " << mapHeight << std::endl << "tileMap depth: " << mapWidth << std::endl;
    }

    for (int i = 0; i < (mapWidth * mapHeight * mapDepth); i++)
    {
        file_object >> tile >> separator;
        std::cout << i << ": " << tile << std::endl;
        tileMatrix.push_back(tile);
    }
}

void TileMap::SetTileSet(TileSet* tileSet)
{
    this->tileSet = tileSet;
}
int& TileMap::At(int x, int y, int z)
{
    /*
    # TODO:
    ENCAPSULAR A FUNÇÃO ACIMA PRIMEIRO
    TODO: Calcular índice de retorno [x][y][z] de tileMatrix (que é um vetor).
    */
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY)
{
    /*
    # TODO:
    Renderiza uma camada do mapa, tile a tile. Note que há dois ajustes a se fazer:
        * Deve-se compensar o deslocamento da cˆmera
        * Deve-se considerar o tamanho de cada tile (use os membros GetTileWidth e GetTileHeight de TileSet)
    Ainda não temos câmera. Você pode deixar para implementar o primeiro ponto naquela oasião, mas já faça a 
    função recebendo esses argumentos.
    */
}

void TileMap::Render()
{
    /*
    # TODO:
    Renderiza as camadas do mapa. Dica: utilize o RenderLayer e o box do GameObject que o contém.
    */
}

int TileMap::GetWidth()
{
    return mapWidth;
}

int TileMap::GetHeight()
{
    return mapHeight;
}

int TileMap::GetDepth()
{
    return mapDepth;
}

bool TileMap::Is(std::string type)
{
    if (type == "TileMap")
    {
        return true;
    }
    else
    {
        return false;
    }
}

void TileMap::Update(float dt) {}