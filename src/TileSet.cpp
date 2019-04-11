#include "../include/TileSet.h"

TileSet::TileSet(GameObject& associated, int tileWidth, int tileHeight, std::string file) : tileSet(associated, file.c_str()),
                                                                                            tileWidth(tileWidth),
                                                                                            tileHeight(tileHeight)
{
    columns = tileSet->GetWidth()/tileWidth;
    rows = tileSet->GetHeight()/tileHeight;
}

void TileSet::RenderTile(unsigned index, float x, float y)
{   
    // Número de tiles é o número de colunas * o número de linhas
    int tilesNumber = columns * rows;
    // std::cout << index << std::endl;
    if (0 <= index)
    {
        if (index <= (unsigned int)(tilesNumber - 1))
        {
            // O resto da divisão do índice pelo número de colunas
            int clipOrgX = index % columns;
            // O quociente da divisão do índice pelo número de colunas
            int clipOrgY = index / columns; 
            tileSet->SetClip(clipOrgX, clipOrgY, tileSet->GetWidth(), tileSet->GetHeight());
            tileSet->Render((int)x, (int)y);
        }
    }
}

int TileSet::GetTileWidth()
{
    return tileWidth;
}

int TileSet::GetTileHeight()
{
    return tileHeight;
}