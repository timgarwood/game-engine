#include "cube.h"
#include "btBulletDynamicsCommon.h"

using namespace std;

Cube::Cube(btCollisionShape *collisionShape, Vector3f center, float faceSize, Vector3f color) : Quad3d(collisionShape, center, faceSize, faceSize, faceSize, color)
{
}