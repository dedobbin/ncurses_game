#include "entity.h"

Entity::Entity(std::string name, int x, int y, bool isPlayer, bool isSolid)
: name(name), x(x), y(y), isPlayer(isPlayer), isSolid(isSolid)
{}

Entity::Entity(std::string name, int x, int y, 
    void (*behaviorCallback)(std::shared_ptr<Entity>, Room*),
    void (*effectCallback)(std::shared_ptr<Entity> self, std::shared_ptr<Entity> other, Room* room),
    bool isSolid
)
: name(name), x(x), y(y), isPlayer(false), behaviorCallback(behaviorCallback), effectCallback(effectCallback), isSolid(isSolid)
{}