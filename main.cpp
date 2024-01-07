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

#ifdef SHADER_TRANSLATION_DEMO
#include "shader-translation-demo.h"
#endif

#ifdef SHADER_ROTATION_DEMO
#include "shader-rotation-demo.h"
#endif

#ifdef SHADER_INTERPOLATION_DEMO
#include "shader-interpolation-demo.h"
#endif

#ifdef INDEX_BUFFER_DEMO
#include "index-buffer-demo.h"
#endif

#ifdef PERSPECTIVE_PROJECTION_DEMO
#include "perspective-projection-demo.h"
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
#elif SHADER_TRANSLATION_DEMO
    ShaderTranslationDemo *std = ShaderTranslationDemo::Instance();
#elif SHADER_ROTATION_DEMO
    ShaderRotationDemo *srd = ShaderRotationDemo::Instance();
#elif SHADER_INTERPOLATION_DEMO
    ShaderInterpolationDemo *sid = ShaderInterpolationDemo::Instance();
#elif INDEX_BUFFER_DEMO
    IndexBufferDemo *ibd = IndexBufferDemo::Instance();
#elif PERSPECTIVE_PROJECTION_DEMO
    PerspectiveProjectionDemo *ppd = PerspectiveProjectionDemo::Instance();
#endif

    e->Init();

    e->MainLoop();

    e->TearDown();
}