#include "entity.h"

Entity::Entity(std::string name, int x, int y, bool isPlayer)
: name(name), x(x), y(y), isPlayer(isPlayer)
{}

Entity::Entity(std::string name, int x, int y, void (*behaviorCallback)(std::shared_ptr<Entity>, Room*))
: name(name), x(x), y(y), isPlayer(isPlayer), behaviorCallback(behaviorCallback)
{}