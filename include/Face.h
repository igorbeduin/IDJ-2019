#include <iostream>

class Face {
    public:
        Face(GameObject& associated);
        void Damage(int damage);
        void Update(float dt);
        void Render();
        bool Is(std::string type);

    private:
        int hitpoints;
}