#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include "single-point-demo.h"
#include "graphics-engine.h"
#include "engine.h"
#include <stddef.h>

SinglePointDemo *SinglePointDemo::s_instance = NULL;

static void init(void)
{
    SinglePointDemo::Instance()->Init();
}

static void render(void)
{
    SinglePointDemo::Instance()->Render();
}

SinglePointDemo::SinglePointDemo()
{
    Engine::Instance()->RegisterModuleInitCallback(init);
    GraphicsEngine::Instance()->RegisterRenderCallback(render);
}

SinglePointDemo *SinglePointDemo::Instance(void)
{
    if (s_instance == NULL)
    {
        s_instance = new SinglePointDemo();
    }

    return s_instance;
}

void SinglePointDemo::Init(void)
{
    m_vertices[0] = Vector3f(0.0f, 0.0f, 0.0f);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);
}

void SinglePointDemo::Render(void)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_POINTS, 0, 1);

    glDisableVertexAttribArray(0);
}