#ifndef _CUBE_H
#define _CUBE_H

#include "quad3d.h"

class Cube : public Quad3d
{
public:
    Cube(btCollisionShape *collisionShape, Vector3f center, float faceSize, Vector3f color);
};

#endif