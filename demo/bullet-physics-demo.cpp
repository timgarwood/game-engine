#include "bullet-physics-demo.h"
#include "engine.h"
#include <stddef.h>
#include <iostream>
#include <cstring>
#include "cube.h"
#include "game-world.h"
#include "btBulletDynamicsCommon.h"
#include "bullet-physics-engine.h"

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
    btCollisionShape *cubeShape = new btBoxShape(btVector3(.5, .5, .5));
    btCollisionShape *floorShape = new btBoxShape(btVector3(5, .05, 5));
    Cube *c1 = new Cube(cubeShape, Vector3f(4, 50, 0), 1, RAND_COLOR);
    c1->SetMass(1.0f);
    c1->BuildRigidBody();
    GameWorld::Instance()->AddDynamic(c1);
    BulletPhysicsEngine::Instance()->AddGameObject(c1);

    Quad3d *c2 = new Quad3d(floorShape, Vector3f(4, -20, 0), 10, .1, 10, RAND_COLOR);
    c2->SetMass(0.0f);
    c2->BuildRigidBody();
    GameWorld::Instance()->AddStatic(c2);
    BulletPhysicsEngine::Instance()->AddGameObject(c2);

    /*Cube *c3 = new Cube(cubeShape, Vector3f(0, 22, 0), 1, RAND_COLOR);
    c3->SetMass(1.0f);
    c3->BuildRigidBody();
    GameWorld::Instance()->AddDynamic(c3);
    BulletPhysicsEngine::Instance()->AddGameObject(c3);

    Cube *c4 = new Cube(cubeShape, Vector3f(0, 21, 0), 1, RAND_COLOR);
    c4->SetMass(1.0f);
    c4->BuildRigidBody();
    GameWorld::Instance()->AddStatic(c4);
    //BulletPhysicsEngine::Instance()->AddGameObject(c4);

    Cube *c5 = new Cube(cubeShape, Vector3f(5, 1, 5), 1, RAND_COLOR);
    c5->SetMass(1.0f);
    c5->BuildRigidBody();
    GameWorld::Instance()->AddDynamic(c5);
    BulletPhysicsEngine::Instance()->AddGameObject(c5);

    Cube *c6 = new Cube(cubeShape, Vector3f(-5, 1, 5), 1, RAND_COLOR);
    c6->SetMass(1.0f);
    c6->BuildRigidBody();
    GameWorld::Instance()->AddDynamic(c6);
    BulletPhysicsEngine::Instance()->AddGameObject(c6);
    */

    // floor
    //Quad3d *floor = new Quad3d(floorShape, Vector3f(0, 10, 0), 50, 20, 50, RAND_COLOR);
    //Quad3d *floor = new Quad3d(floorShape, Vector3f(4, 20, 0), 1, 1, 1, RAND_COLOR);
    //floor->SetMass(0.0f);
    //floor->BuildRigidBody();
    //GameWorld::Instance()->AddStatic(floor);
    //BulletPhysicsEngine::Instance()->AddGameObject(floor);
}