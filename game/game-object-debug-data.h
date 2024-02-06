#ifndef _GAME_OBJECT_DEBUG_DATA_H
#define _GAME_OBJECT_DEBUG_DATA_H

#include "vector.h"
#include "matrix.h"

struct GameObjectDebugData
{
    Vector3f position;

    // rotation matrix
    Matrix4f rotation;

    // each debug game object is a Quad3d
    float width;
    float height;
    float depth;

    // physics properties
    float mass;
    bool isDynamic;

    // color
    Vector3f color;
};

#endif