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
        std::cout << "TileMap:  tileMap width: " << mapWidth << std::endl  << "tileMap height: " << mapHeight << std::endl << "tileMap depth: " << mapWidth << std::endl;
    }

    for (int i = 0; i < (mapWidth * mapHeight * mapDepth); i++)
    {
        file_object >> tile >> separator;
        // std::cout << i << ": " << tile << std::endl;
        tileMatrix.push_back(tile - 1);
    }
}

void TileMap::SetTileSet(TileSet* tileSet)
{
    this->tileSet = tileSet;
}
int& TileMap::At(int x, int y, int z)
{
    int index = x + (y * mapWidth) + (z * mapWidth * mapHeight);
    int& reference = tileMatrix[index];

    return reference;
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY)
{
    for (int x = 0; x < mapWidth; x++)
    {
        for (int y = 0; x < mapHeight; y++)
        {
            // std::cout << "TileMap:  Ta entrando aqui" << std::endl;
            tileSet->RenderTile(At(x, y, layer),
                                (float)(x + tileSet->GetTileWidth()),
                                (float)(y + tileSet->GetTileHeight()));
        }
    }
}

void TileMap::Render()
{
    for (int i = 0; i < mapDepth; i++)
    {
        RenderLayer(i);
    }
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