#include "engine.h"
#include "graphics-engine.h"
#include "sdl-event-dispatcher.h"
#include "raycaster.h"

int main(int argc, char **argv)
{
    Engine *e = Engine::Instance();
    SDLEventDispatcher::Instance();
    GraphicsEngine *g = GraphicsEngine::Instance();
    Raycaster *r = Raycaster::Instance();

    e->Init();

    e->MainLoop();

    e->TearDown();

    return 0;
}