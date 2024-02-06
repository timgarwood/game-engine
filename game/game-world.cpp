#include "game-world.h"
#include <algorithm>

using namespace std;

GameWorldIF *GameWorld::instance = NULL;

GameWorldIF *GameWorld::Instance()
{
    if (instance == NULL)
    {
        instance = new GameWorld();
    }

    return instance;
}

void GameWorld::AddStatic(GameObjectIF *object)
{
    m_statics.push_back(object);
}

void GameWorld::AddDynamic(GameObjectIF *object)
{
    m_dynamics.push_back(object);
}

void GameWorld::RemoveStatic(GameObjectIF *object)
{
    auto iter = find(m_statics.begin(), m_statics.end(), object);
    if (iter != m_statics.end())
    {
        m_statics.erase(iter);
    }
}

void GameWorld::RemoveDynamic(GameObjectIF *object)
{
    auto iter = find(m_dynamics.begin(), m_dynamics.end(), object);
    if (iter != m_dynamics.end())
    {
        m_dynamics.erase(iter);
    }
}

vector<GameObjectIF *> GameWorld::GetStatics()
{
    return m_statics;
}

vector<GameObjectIF *> GameWorld::GetDynamics()
{
    return m_dynamics;
}