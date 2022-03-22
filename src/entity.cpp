#include "entity.h"

Entity::Entity(std::string name, int x, int y, bool isSolid)
: name(name), x(x), y(y), isSolid(isSolid)
{}

std::shared_ptr<Entity> EntityBuilder::player(std::string name, int x, int y,
        void (*effectCallback)(std::shared_ptr<Entity>, std::shared_ptr<Entity>, Room*)
    )
{
    auto player = std::make_shared<Entity>(name, x, y, true);
    player->effectCallback = effectCallback;
    player->isPlayer = true;
    return player;
}

std::shared_ptr<Entity> EntityBuilder::enemy(std::string name, int x, int y, bool isSolid,
    void (*behaviorCallback)(std::shared_ptr<Entity>, Room*),
    void (*effectCallback)(std::shared_ptr<Entity>, std::shared_ptr<Entity>, Room*)
){
    auto enemy = std::make_shared<Entity>(name, x, y, isSolid);
    enemy->behaviorCallback = behaviorCallback;
    enemy->effectCallback = effectCallback;
    return enemy;
}