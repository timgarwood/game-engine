#ifndef _GAME_OBJECT_H
#define _GAME_OBJECT_H

#include "game-object-if.h"

class btRigidBody;
class btCollisionShape;

class GameObject : public GameObjectIF
{
public:
    GameObject(btCollisionShape *collisionShape);

    // get the vertices of the game object
    virtual const std::vector<Vector3f> &GetVertices();

    // get the vertex buffer indices to render
    virtual const std::vector<int> &GetIndices();

    virtual Matrix4f GetRotation();

    virtual Vector3f GetPosition();

    virtual void SetMass(float mass);

    virtual void SetStartPosition(Vector3f startTransform);

    virtual void SetStartRotation(float angleX, float angleY, float angleZ);

    virtual const Matrix4f &GetStartOffset();

    virtual void BuildRigidBody();

    virtual btRigidBody *GetRigidBody();

    virtual bool IsCollidable();

    virtual void SetColor(Vector3f color);

    virtual Vector3f GetColor();

protected:
    std::vector<Vector3f> m_vertices;
    std::vector<int> m_indices;

    float m_mass;
    Vector3f m_startPosition;
    Vector3f m_startRotation;
    Matrix4f m_startOffset;
    btCollisionShape *m_collisionShape;
    btRigidBody *m_rigidBody;
    Vector3f m_color;
};

#endif