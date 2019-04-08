#include "../include/TileMap.h"

TileMap::TileMap(GameObject &associated, std::string file, TileSet *tileSet) : Component::Component(associated),
                                                                               tileSet(tileSet)
{
    TileMap::Load(file.c_str());
}

void TileMap::Load(std::string file)
{
    /*
    # TODO: 
    Carregar um arquivo de mapa, no formato dado pelo arquivo map/tileMap.txt.
    Os primeiros três números são as dimensões do mapa: largura, altura e profundidade.
    Em seguida, vêm os tiles, que devem ser carregados em ordem para a matriz de tiles.

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
    Tenderiza as camadas do mapa. Dica: utilize o RenderLayer e o box do GameObject que o contém.
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