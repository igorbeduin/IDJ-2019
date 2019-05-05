
#include <iostream>

#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"

class Alien : public Component
{
  public:
    Alien(GameObject &associated, int nMinions);
    ~Alien();
    void Start();
    void Update(float dt);
    void Render();
    bool Is(std::string type);

  private:
    class Action
    {
      public:
        Action(ActionType type, float x, float y);
        enum ActionType;
        ActionType type;
        Vec2 pos;
    };
    Vec2 speed;
    int hp;
    std::queue<Action> taskQueue;
    std::vector<std::weak_ptr<GameObject>> minionArray;
};