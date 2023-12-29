#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "engine-api.h"
#include "graphics-engine.h"
#include "single-point-demo.h"

int main(int argc, char **argv)
{
    Engine *e = Engine::Instance();
    GraphicsEngine *g = GraphicsEngine::Instance();
    SinglePointDemo *spd = SinglePointDemo::Instance();

    e->Init();

    e->MainLoop();

    e->TearDown();
}