#include "game-object.h"
#include <cassert>
#include "btBulletDynamicsCommon.h"
#include <cmath>

using namespace std;

GameObject::GameObject(btCollisionShape *collisionShape)
{
    m_collisionShape = collisionShape;
    m_rigidBody = NULL;
    m_color = Vector3f(1, 1, 1);
    m_startRotation = Vector3f(0, 0, 0);
}

const vector<Vector3f> &GameObject::GetVertices()
{
    return m_vertices;
}

const vector<int> &GameObject::GetIndices()
{
    return m_indices;
}

void GameObject::SetMass(float mass)
{
    m_mass = mass;
}

void GameObject::SetStartPosition(Vector3f startPosition)
{
    m_startOffset.SetIdentity();
    m_startOffset.matrix[0][3] = -startPosition.x;
    m_startOffset.matrix[1][3] = -startPosition.y;
    m_startOffset.matrix[2][3] = -startPosition.z;
    m_startPosition = startPosition;
}

void GameObject::SetStartRotation(float angleX, float angleY, float angleZ)
{
    m_startRotation.x = angleX;
    m_startRotation.y = angleY;
    m_startRotation.z = angleZ;
}

const Matrix4f &GameObject::GetStartOffset()
{
    return m_startOffset;
}

Vector3f GameObject::GetPosition()
{
    btTransform bulletTransform;
    m_rigidBody->getMotionState()->getWorldTransform(bulletTransform);

    return Vector3f(bulletTransform.getOrigin()[0],
                    bulletTransform.getOrigin()[1],
                    bulletTransform.getOrigin()[2]);
}

Matrix4f GameObject::GetRotation()
{
    btTransform bulletTransform;
    m_rigidBody->getMotionState()->getWorldTransform(bulletTransform);

    Matrix4f ret;
    auto basis = bulletTransform.getBasis();

    ret.Set(&basis);

    return ret;
}

void GameObject::BuildRigidBody()
{
    btTransform startTransform;
    startTransform.setIdentity();
    startTransform.setOrigin(btVector3(m_startPosition.x, m_startPosition.y, m_startPosition.z));

    btQuaternion quat;
    // setEuler takes y,x,z in that order
    quat.setEuler(m_startRotation.y, m_startRotation.x, m_startRotation.z);
    startTransform.setRotation(quat);

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

Vector3f GameObject::GetColor()
{
    return m_color;
}

void GameObject::SetColor(Vector3f color)
{
    m_color = color;
}