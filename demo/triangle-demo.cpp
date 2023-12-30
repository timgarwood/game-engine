#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include "triangle-demo.h"
#include "graphics-engine.h"
#include "engine.h"
#include <stddef.h>

TriangleDemo *TriangleDemo::s_instance = NULL;

static void init(void)
{
    TriangleDemo::Instance()->Init();
}

static void render(void)
{
    TriangleDemo::Instance()->Render();
}

TriangleDemo::TriangleDemo()
{
    Engine::Instance()->RegisterModuleInitCallback(init);
    GraphicsEngine::Instance()->RegisterRenderCallback(render);
}

TriangleDemo *TriangleDemo::Instance(void)
{
    if (s_instance == NULL)
    {
        s_instance = new TriangleDemo();
    }

    return s_instance;
}

void TriangleDemo::Init(void)
{
    m_vertices[0] = Vector3f(0.0f, 0.0f, 0.0f);
    m_vertices[1] = Vector3f(0.5f, 0.5f, 0.0f);
    m_vertices[2] = Vector3f(0.5f, 0.0f, 0.0f);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);
}

void TriangleDemo::Render(void)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_TRIANGLES, 0, sizeof(m_vertices) / (sizeof(Vector3f)));

    glDisableVertexAttribArray(0);
}