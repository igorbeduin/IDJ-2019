#include "../include/Component.h"
#include "../include/GameObject.h"

Component::Component(GameObject& associated) : associated(associated) {
}
Component::~Component()
{
}