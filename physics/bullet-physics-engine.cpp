#include "bullet-physics-engine.h"
#include "btBulletDynamicsCommon.h"
#include "engine-api.h"
#include "game-object-if.h"

BulletPhysicsEngine *BulletPhysicsEngine::instance = NULL;

static FrameCallbackResult bullet_physics_engine_next_frame()
{
    return BulletPhysicsEngine::Instance()->NextFrame();
}

BulletPhysicsEngine *BulletPhysicsEngine::Instance()
{
    if (instance == NULL)
    {
        instance = new BulletPhysicsEngine();
    }

    return instance;
}

BulletPhysicsEngine::BulletPhysicsEngine()
{
    engine_register_frame_callback(bullet_physics_engine_next_frame);

    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);
    overlappingPairCache = new btDbvtBroadphase();
    solver = new btSequentialImpulseConstraintSolver;
    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

    dynamicsWorld->setGravity(btVector3(0, -10, 0));
}

FrameCallbackResult BulletPhysicsEngine::NextFrame()
{
    dynamicsWorld->stepSimulation(1.0f / 60.0f, 10);

    // print positions of all objects
    for (int j = dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--)
    {
        btCollisionObject *obj = dynamicsWorld->getCollisionObjectArray()[j];
        btRigidBody *body = btRigidBody::upcast(obj);
        btTransform trans;
        if (body && body->getMotionState())
        {
            body->getMotionState()->getWorldTransform(trans);
        }
        else
        {
            trans = obj->getWorldTransform();
        }
        printf("world pos object %d = %f,%f,%f\n", j, float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
    }

    return CONTINUE;
}

void BulletPhysicsEngine::AddGameObject(GameObjectIF *gameObject)
{
    if (gameObject->IsCollidable())
    {
        dynamicsWorld->addRigidBody(gameObject->GetRigidBody());
    }
}