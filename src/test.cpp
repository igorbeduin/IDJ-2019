// vector iterator test
#include <iostream>
#include <vector>

int main() {
    std::vector<int> bla;

    bla.push_back(6);
    bla.push_back(8);
    bla.push_back(9);
    bla.push_back(14);

    for (int i = 0; i < bla.size(); i++)
    {
        std::cout << bla[i] << std::endl;
    }

    for (int i = 0; i != bla.size(); i++) {
        if (bla[i] == 9) {
            bla.erase(bla.begin()+i);
        }
    }

    for (int i = 0; i < bla.size(); i++) {
        std::cout << bla[i] << std::endl;
    }

    return 0;
}