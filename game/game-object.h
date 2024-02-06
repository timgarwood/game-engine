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

    virtual const Matrix4f &GetRotation();

    virtual const Matrix4f &GetTranslation();

    virtual void SetMass(float mass);

    virtual void SetStartPosition(Vector3f startTransform);

    virtual void BuildRigidBody();

    virtual btRigidBody *GetRigidBody();

    virtual bool IsCollidable();

    virtual Matrix4f GetPhysicsTransform();

protected:
    std::vector<Vector3f> m_vertices;
    std::vector<int> m_indices;

    Matrix4f m_rotation;
    Matrix4f m_translation;
    float m_mass;
    Vector3f m_startPosition;
    btCollisionShape *m_collisionShape;
    btRigidBody *m_rigidBody;
};

#endif