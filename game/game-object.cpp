#include "game-object.h"
#include <cassert>
#include "btBulletDynamicsCommon.h"

using namespace std;

GameObject::GameObject(btCollisionShape *collisionShape)
{
    m_collisionShape = collisionShape;
    m_rigidBody = NULL;
}

const vector<Vector3f> &GameObject::GetVertices()
{
    return m_vertices;
}

const vector<int> &GameObject::GetIndices()
{
    return m_indices;
}

const Matrix4f &GameObject::GetRotation()
{
    return m_rotation;
}

const Matrix4f &GameObject::GetTranslation()
{
    return m_translation;
}

void GameObject::SetMass(float mass)
{
    m_mass = mass;
}

void GameObject::SetStartPosition(Vector3f startPosition)
{
    m_startPosition = startPosition;
}

void GameObject::BuildRigidBody()
{
    btTransform startTransform;
    startTransform.setIdentity();
    startTransform.setOrigin(btVector3(m_startPosition.x, m_startPosition.y, m_startPosition.z));

    // rigidbody is dynamic if and only if mass is non zero, otherwise static
    bool isDynamic = (m_mass != 0.f);

    btScalar mass(m_mass);

    btVector3 localInertia(0, 0, 0);
    if (isDynamic)
        m_collisionShape->calculateLocalInertia(mass, localInertia);

    // using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
    btDefaultMotionState *myMotionState = new btDefaultMotionState(startTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, m_collisionShape, localInertia);
    m_rigidBody = new btRigidBody(rbInfo);
}

btRigidBody *GameObject::GetRigidBody()
{
    assert(m_rigidBody != NULL);
    return m_rigidBody;
}

bool GameObject::IsCollidable()
{
    return m_collisionShape != NULL && m_rigidBody != NULL;
}

Matrix4f GameObject::GetPhysicsTransform()
{
    Matrix4f ret;
    ret.SetIdentity();
    btTransform bulletTransform;
    //if (m_mass != 0.f)
    // {
    m_rigidBody->getMotionState()->getWorldTransform(bulletTransform);
    // }
    // else
    // {
    //     bulletTransform = m_rigidBody->getWorldTransform();
    // }

    btVector3 translation = bulletTransform.getOrigin();
    btMatrix3x3 rotation = bulletTransform.getBasis();
    ret.matrix[0][3] = translation[0] - m_startPosition.x;
    ret.matrix[1][3] = translation[1] - m_startPosition.y;
    ret.matrix[2][3] = translation[2] - m_startPosition.z;

    ret.matrix[0][0] = rotation[0][0];
    ret.matrix[0][1] = rotation[0][1];
    ret.matrix[0][2] = rotation[0][2];

    ret.matrix[1][0] = rotation[1][0];
    ret.matrix[1][1] = rotation[1][1];
    ret.matrix[1][2] = rotation[1][2];

    ret.matrix[2][0] = rotation[2][0];
    ret.matrix[2][1] = rotation[2][1];
    ret.matrix[2][2] = rotation[2][2];

    float ogl[16];
    bulletTransform.getOpenGLMatrix(ogl);

    ogl[3] = ogl[12];
    ogl[7] = ogl[13];
    ogl[11] = ogl[14];

    ogl[12] = 0;
    ogl[13] = 0;
    ogl[14] = 0;
    ogl[15] = 1;

    ogl[3] -= m_startPosition.x;
    ogl[7] -= m_startPosition.y;
    ogl[11] -= m_startPosition.z;

    return Matrix4f(ogl);

    //return ret;
}