#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "engine-api.h"
#include "graphics-engine.h"

#ifdef SINGLE_POINT_DEMO
#include "single-point-demo.h"
#endif

#ifdef TRIANGLE_DEMO
#include "triangle-demo.h"
#endif

#ifdef SHADER_UNIFORM_DEMO
#include "shader-uniform-demo.h"
#endif

int main(int argc, char **argv)
{
    Engine *e = Engine::Instance();
    GraphicsEngine *g = GraphicsEngine::Instance();
#ifdef SINGLE_POINT_DEMO
    SinglePointDemo *spd = SinglePointDemo::Instance();
#elif TRIANGLE_DEMO
    TriangleDemo *td = TriangleDemo::Instance();
#elif SHADER_UNIFORM_DEMO
    ShaderUniformDemo *sud = ShaderUniformDemo::Instance();
#endif

    e->Init();

    e->MainLoop();

    e->TearDown();
}