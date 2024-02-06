#ifndef _GAME_WORLD_IF_H
#define _GAME_WORLD_IF_H

#include <vector>

class GameObjectIF;

class GameWorldIF
{
public:
    virtual void AddStatic(GameObjectIF *object) = 0;
    virtual void AddDynamic(GameObjectIF *object) = 0;
    virtual void RemoveStatic(GameObjectIF *object) = 0;
    virtual void RemoveDynamic(GameObjectIF *object) = 0;

    virtual std::vector<GameObjectIF *> GetStatics() = 0;
    virtual std::vector<GameObjectIF *> GetDynamics() = 0;
};

#endif