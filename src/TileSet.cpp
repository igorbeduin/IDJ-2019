#include "../include/TileSet.h"

TileSet::TileSet(int tileWidth, int tileHeight, std::string file) : tileWidth(tileWidth),
                                                                    tileHeight(tileHeight)
{
    tileSet.Open(file.c_str());
    // TODO: Descobrir pelo tamanho do sprite o número de linhas e colunas
}

void TileSet::RenderTile(unsigned index, float x, float y)
{
    // TODO: verificar se o índice é valido. 
    // Se sim, setar o clip recortando e renderizando na posição desejada

    // TODO: Fazer overload de operador de Sprite::Render
}

int GetTileWidth()
{
    return tileWidth;
}

int GetTileHeight()
{
    return tileHeight;
}