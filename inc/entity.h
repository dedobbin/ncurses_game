#pragma once
#include <string>
#include <memory>
struct Room; //forward declaration because circular dependency

struct Entity 
{
    Entity(std::string name, int x, int y, bool isSolid=true);
    const std::string name;
    int x, y;
    bool isPlayer=false;
    bool isSolid=true;
    void (*behaviorCallback)(std::shared_ptr<Entity> self, Room* room);
    void (*effectCallback)(std::shared_ptr<Entity> self, std::shared_ptr<Entity> other, Room* room);
};

struct Wall
{
    int x,y;
};

struct EntityBuilder
{
    static std::shared_ptr<Entity> player(std::string name, int x, int y,
        void (*effectCallback)(std::shared_ptr<Entity>, std::shared_ptr<Entity>, Room*)
    );
    
    static std::shared_ptr<Entity> enemy(std::string name, int x, int y, bool isSolid,
        void (*behaviorCallback)(std::shared_ptr<Entity>, Room*),
        void (*effectCallback)(std::shared_ptr<Entity>, std::shared_ptr<Entity>, Room*)
    );
};