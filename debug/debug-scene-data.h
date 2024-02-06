#ifndef _DEBUG_SCENE_DATA_H
#define _DEBUG_SCENE_DATA_H

#include "vector.h"
#include <vector>
#include "game-object-debug-data.h"

struct DebugSceneData
{
    DebugSceneData();
    Vector3f cameraPosition;
    Vector3f cameraLookAt;
    std::vector<GameObjectDebugData> gameObjectDebugData;
};

#endif