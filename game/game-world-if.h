#ifndef _GAME_WORLD_IF_H
#define _GAME_WORLD_IF_H

#include <vector>

class GameObjectIF;

class GameWorldIF
{
public:
    virtual void AddObject(GameObjectIF *object) = 0;
    virtual void RemoveObject(GameObjectIF *object) = 0;

    virtual std::vector<GameObjectIF *> GetObjects() = 0;
};

#endif