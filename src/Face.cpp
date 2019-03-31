#include "../include/Face.h"

Face::Face(GameObject& associated) {
    // Construir a classe mãe
    hitpoints = 30;
}

Face::Damage(int damage) {
    hitpoints = hitpoints - damage;
    if (hitpoints <= 0) {
        associated.RequestDelete();
        // Da play no sound se houver um
    }
}

void Update(float dt) {}
void Render() {}

bool Is(std::string type) {
    if (type == "Face") {
        return true;
    } else {
        return false;
    }
}

