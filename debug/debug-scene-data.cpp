#include "debug-scene-data.h"
#include <cstring>

DebugSceneData::DebugSceneData()
{
    memset(&cameraPosition, 0, sizeof(Vector3f));
    memset(&cameraLookAt, 0, sizeof(Vector3f));
}