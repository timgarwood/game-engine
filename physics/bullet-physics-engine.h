#ifndef _BULLET_PHYSICS_ENGINE_H
#define _BULLET_PHYSICS_ENGINE_H

#include "engine.h"

class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btBroadphaseInterface;
class btSequentialImpulseConstraintSolver;
class btDiscreteDynamicsWorld;
class GameObjectIF;

class BulletPhysicsEngine
{
public:
    void Init();
    void Teardown();
    void AddGameObject(GameObjectIF *gameObject);
    FrameCallbackResult NextFrame();
    static BulletPhysicsEngine *Instance();

private:
    BulletPhysicsEngine();
    static BulletPhysicsEngine *instance;

    btDefaultCollisionConfiguration *collisionConfiguration;
    btCollisionDispatcher *dispatcher;
    btBroadphaseInterface *overlappingPairCache;
    btSequentialImpulseConstraintSolver *solver;
    btDiscreteDynamicsWorld *dynamicsWorld;
};

#endif