#include "engine-api.h"
#include "graphics-engine.h"

int main(int argc, char **argv)
{
    Engine *e = Engine::Instance();
    GraphicsEngine *g = GraphicsEngine::Instance();

    e->Init();

    e->MainLoop();

    e->TearDown();
}