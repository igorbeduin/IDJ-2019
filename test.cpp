#include <iostream>
#include <fstream>

int main() 
{
    int x, y, z;
    char bla;
    std::ifstream file_object;
    file_object.open("assets/map/tileMap.txt");
    if (file_object)
    {
        std::cout << "Arquivo foi aberto com sucesso!" << std::endl;

        for (int i = 0; i < 3; i++)
        {
            file_object >> x >> bla;
            std::cout << "int: " << x << std::endl
                      << "char: " << y << std::endl;
        }
    }
}