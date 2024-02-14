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

void GameWorld::AddObject(GameObjectIF *object)
{
    m_objects.push_back(object);
}

void GameWorld::RemoveObject(GameObjectIF *object)
{
    auto iter = find(m_objects.begin(), m_objects.end(), object);
    if (iter != m_objects.end())
    {
        m_objects.erase(iter);
    }
}

vector<GameObjectIF *> GameWorld::GetObjects()
{
    return m_objects;
}