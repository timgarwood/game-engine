#ifndef _QUAD3D_H
#define _QUAD3D_H

/**
 * A generic class for drawing a 6 sided 3d object, for programmatically creating floors, ramps, walls, etc.
 */

#include "vector.h"
#include "math.h"
#include <vector>
#include "game-object.h"

class Quad3d : public GameObject
{
public:
    Quad3d(btCollisionShape *collisionShape, Vector3f center, float faceLength, float height, float depth);
    Quad3d(btCollisionShape *collisionShape, Vector3f center, float faceLength, float height, float depth, Vector3f color);
    Vector3f GetCenter();
    Vector3f GetColor();

private:
    Vector3f m_center;
    Vector3f m_color;
};

#endif