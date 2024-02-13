#ifndef _GAME_OBJECT_IF_H
#define _GAME_OBJECT_IF_H

#include <vector>
#include "vector.h"
#include "matrix.h"

class btRigidBody;

class GameObjectIF
{
public:
    // get the vertices of the game object
    virtual const std::vector<Vector3f> &GetVertices() = 0;

    // get the vertex buffer indices to render
    virtual const std::vector<int> &GetIndices() = 0;

    virtual Matrix4f GetRotation() = 0;

    virtual Vector3f GetPosition() = 0;

    virtual void SetMass(float mass) = 0;

    virtual void SetStartPosition(Vector3f startTransform) = 0;

    virtual const Matrix4f &GetStartOffset() = 0;

    virtual void BuildRigidBody() = 0;

    virtual btRigidBody *GetRigidBody() = 0;

    virtual bool IsCollidable() = 0;

    virtual void SetColor(Vector3f color) = 0;

    virtual Vector3f GetColor() = 0;
};

#endif