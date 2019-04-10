#include "../include/TileMap.h"

TileMap::TileMap(GameObject &associated, std::string file, TileSet *tileSet) : Component::Component(associated),
                                                                               tileSet(tileSet)
{
    TileMap::Load(file.c_str());
}

TileMap::TileMap(GameObject &associated, std::string file) : Component::Component(associated)
{
    TileMap::Load(file.c_str());
}

void TileMap::Load(std::string file)
{   
    int width, height, depth;
    char separator;
    std::ifstream file_object;
    file_object.open(file.c_str());
    // Garante que o arquivo foi aberto corretamente
    if (file_object) 
    {
        // Pega os três primeiros valores do arquivo tileMap.txt
        file_object >> width >> separator >> height >> separator >> depth;
        std::cout << "tileMap width: " << width << std::endl  << "tileMap height: " << height << std::endl << "tileMap depth: " << width << std::endl;
    }

    if (file_object)
    {
        // TODO: Rotina para carregar os tiles em ordem correta na matriz >> SUBTRAIR 1<<

    }

    /*
    Note que, para o arquivo que usamos na disciplina, tiles vazios são representados por 0,
    que é o padrão do editor de tilemaps open spurce TileD.
    Para o nosso código, é mais conveniente que eles sejam representados por - 1,
     e o primeiro tile do tileset por 0. Portanto, subtraia um de cada índice lido do arquivo.
    */
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