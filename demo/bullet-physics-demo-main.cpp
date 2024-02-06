#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "engine-api.h"
#include "graphics-engine.h"
#include "sdl-event-dispatcher.h"
#include "fps-camera-controller.h"
#include "bullet-physics-engine.h"
#include "bullet-physics-demo.h"
#include "game-object-renderer.h"

int main(int argc, char **argv)
{
    Engine *e = Engine::Instance();
    BulletPhysicsEngine::Instance();
    SDLEventDispatcher::Instance();
    GraphicsEngine *g = GraphicsEngine::Instance();
    FPSCameraController::Instance();
    BulletPhysicsDemo *bpd = BulletPhysicsDemo::Instance();
    GameObjectRenderer *gor = GameObjectRenderer::Instance();

    e->Init();

    e->MainLoop();

    e->TearDown();
}