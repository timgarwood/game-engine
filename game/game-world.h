#ifndef _GAME_WORLD_H
#define _GAME_WORLD_H

#include "game-world-if.h"

class GameWorld : public GameWorldIF
{
public:
    static GameWorldIF *Instance();

private:
    static GameWorldIF *instance;
    virtual void AddStatic(GameObjectIF *object);
    virtual void AddDynamic(GameObjectIF *object);
    virtual void RemoveStatic(GameObjectIF *object);
    virtual void RemoveDynamic(GameObjectIF *object);

    virtual std::vector<GameObjectIF *> GetStatics();
    virtual std::vector<GameObjectIF *> GetDynamics();

    std::vector<GameObjectIF *> m_statics;
    std::vector<GameObjectIF *> m_dynamics;
};

#endif