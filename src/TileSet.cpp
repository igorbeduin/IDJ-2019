#include "../include/TileSet.h"

TileSet::TileSet(GameObject& associated, int tileWidth, int tileHeight, std::string file) : tileSet(associated, file.c_str()),
                                                                                            tileWidth(tileWidth),
                                                                                            tileHeight(tileHeight)
{
    columns = tileSet.GetWidth()/tileWidth;
    rows = tileSet.GetHeight()/tileHeight;
    tilesNumber = columns * rows;
}

void TileSet::RenderTile(unsigned index, float x, float y)
{   
    if (0 <= index)
    {
        if (index <= (unsigned int)(tilesNumber - 1))
        {   
            int OrgX = tileWidth*(index%columns);
            int OrgY = tileHeight*(index/columns);
            //std::cout << "OrgX: " << OrgX << "|" << "OrgY: " << OrgY << "|" << "index: " << index << std::endl;
            tileSet.SetClip(OrgX, OrgY, tileWidth, tileHeight);
            tileSet.Render((int)x, (int)y);
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