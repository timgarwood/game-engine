#ifndef _GAME_WORLD_H
#define _GAME_WORLD_H

#include "game-world-if.h"

class GameWorld : public GameWorldIF
{
public:
    static GameWorldIF *Instance();

private:
    static GameWorldIF *instance;
    virtual void AddObject(GameObjectIF *object);
    virtual void RemoveObject(GameObjectIF *object);

    virtual std::vector<GameObjectIF *> GetObjects();

    std::vector<GameObjectIF *> m_objects;
};

#endif