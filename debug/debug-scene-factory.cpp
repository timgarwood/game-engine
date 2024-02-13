#include "debug-scene-factory.h"
#include "debug-scene-parser.h"
#include "debug-scene-data.h"
#include "camera.h"
#include "quad3d.h"
#include "game-world.h"
#include "btBulletDynamicsCommon.h"
#include "bullet-physics-engine.h"

using namespace std;

DebugSceneFactory *DebugSceneFactory::instance = NULL;

DebugSceneFactory::DebugSceneFactory()
{
}

DebugSceneFactory *DebugSceneFactory::Instance()
{
    if (instance == NULL)
    {
        instance = new DebugSceneFactory();
    }

    return instance;
}

void DebugSceneFactory::LoadScene(const string &filename)
{
    DebugSceneParser parser;
    DebugSceneData debugSceneData = parser.LoadDebugSceneData(filename);

    //Camera::Instance()->SetPosition(debugSceneData.cameraPosition);
    //Camera::Instance()->SetLookAt(debugSceneData.cameraLookAt);

    auto iter = debugSceneData.gameObjectDebugData.begin();
    for (; iter != debugSceneData.gameObjectDebugData.end(); ++iter)
    {
        btCollisionShape *collisionShape = new btBoxShape(btVector3(iter->width / 2, iter->height / 2, iter->depth / 2));
        auto q3d = new Quad3d(collisionShape, iter->position, iter->width, iter->height, iter->depth, iter->color);
        q3d->SetMass(iter->mass);
        q3d->BuildRigidBody();
        if (iter->mass != 0.f)
        {
            GameWorld::Instance()->AddDynamic(q3d);
        }
        else
        {
            GameWorld::Instance()->AddStatic(q3d);
        }

        BulletPhysicsEngine::Instance()->AddGameObject(q3d);
    }
}