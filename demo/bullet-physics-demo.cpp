#include "bullet-physics-demo.h"
#include "engine.h"
#include <stddef.h>
#include <iostream>
#include <cstring>
#include "cube.h"
#include "game-world.h"
#include "btBulletDynamicsCommon.h"
#include "bullet-physics-engine.h"
#include "debug-scene-factory.h"

using namespace std;

float max_color = 255.0f;
#define RAND_COLOR Vector3f((float)(rand() % 255) / max_color, (float)(rand() % 255) / max_color, (float)(rand() % 255) / max_color)

BulletPhysicsDemo *BulletPhysicsDemo::s_instance = NULL;

static void init(void)
{
    BulletPhysicsDemo::Instance()->Init();
}

BulletPhysicsDemo::BulletPhysicsDemo()
{
    Engine::Instance()->RegisterModuleInitCallback(init);
}

BulletPhysicsDemo *BulletPhysicsDemo::Instance(void)
{
    if (s_instance == NULL)
    {
        s_instance = new BulletPhysicsDemo();
    }

    return s_instance;
}

void BulletPhysicsDemo::Init(void)
{
    DebugSceneFactory::Instance()->LoadScene("./debug/bullet-physics-demo.json");
}