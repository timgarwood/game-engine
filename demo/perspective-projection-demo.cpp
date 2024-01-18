#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include "perspective-projection-demo.h"
#include "graphics-engine.h"
#include "engine.h"
#include <stddef.h>
#include <iostream>
#include <cstring>
#include "file-utils.h"
#include <time.h>
#include <cmath>
#include "shader-factory.h"
#include "shader-program.h"

using namespace std;

float max_color = 255.0f;
#define RAND_COLOR Vector3f((float)(rand() % 255) / max_color, (float)(rand() % 255) / max_color, (float)(rand() % 255) / max_color)

static float m_cameraDelta = 0.0;

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

PerspectiveProjectionDemo *PerspectiveProjectionDemo::s_instance = NULL;

static void init(void)
{
    PerspectiveProjectionDemo::Instance()->Init();
}

static void render(void)
{
    PerspectiveProjectionDemo::Instance()->Render();
}

PerspectiveProjectionDemo::PerspectiveProjectionDemo()
{
    Engine::Instance()->RegisterModuleInitCallback(init);
    GraphicsEngine::Instance()->RegisterRenderCallback(render);
}

PerspectiveProjectionDemo *PerspectiveProjectionDemo::Instance(void)
{
    if (s_instance == NULL)
    {
        s_instance = new PerspectiveProjectionDemo();
    }

    return s_instance;
}

void PerspectiveProjectionDemo::Init(void)
{
    ShaderFactory::Instance()->LoadShaders("./demo/perspective-projection-demo-shaders.json");
    m_shaderProgram = ShaderFactory::Instance()->GetShaderProgram("main");

    time_t t;
    srand((unsigned)time(&t));

    m_delta = 0.04f;
    m_rotation = 0.0f;

    m_perspectiveProjection = Matrix4f(1, 0, 0, 0,
                                       0, 1, 0, 0,
                                       0, 0, 1, 0,
                                       0, 0, 0, 1);

    m_vertices[0] = Vertex3f(Vector3f(0.5f, 0.5f, 0.5f), RAND_COLOR);
    m_vertices[1] = Vertex3f(Vector3f(-0.5f, 0.5f, -0.5f), RAND_COLOR);
    m_vertices[2] = Vertex3f(Vector3f(-0.5f, 0.5f, 0.5f), RAND_COLOR);
    m_vertices[3] = Vertex3f(Vector3f(0.5f, -0.5f, -0.5f), RAND_COLOR);
    m_vertices[4] = Vertex3f(Vector3f(-0.5f, -0.5f, -0.5f), RAND_COLOR);
    m_vertices[5] = Vertex3f(Vector3f(0.5f, 0.5f, -0.5f), RAND_COLOR);
    m_vertices[6] = Vertex3f(Vector3f(0.5f, -0.5f, 0.5f), RAND_COLOR);
    m_vertices[7] = Vertex3f(Vector3f(-0.5f, -0.5f, 0.5f), RAND_COLOR);

    m_indexes[0] = Vector3i(0, 1, 2);
    m_indexes[1] = Vector3i(1, 3, 4);
    m_indexes[2] = Vector3i(5, 6, 3);
    m_indexes[3] = Vector3i(7, 3, 6);
    m_indexes[4] = Vector3i(2, 4, 7);
    m_indexes[5] = Vector3i(0, 7, 6);
    m_indexes[6] = Vector3i(0, 5, 1);
    m_indexes[7] = Vector3i(1, 5, 3);
    m_indexes[8] = Vector3i(5, 0, 6);
    m_indexes[9] = Vector3i(7, 4, 3);
    m_indexes[10] = Vector3i(2, 1, 4);
    m_indexes[11] = Vector3i(0, 2, 7);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &m_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indexes), m_indexes, GL_STATIC_DRAW);

    m_shaderProgram->Enable();

    m_transformationLocation = (GLuint)m_shaderProgram->GetUniformLocation("gTransformation");
}

void PerspectiveProjectionDemo::Render(void)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    m_rotation += m_delta;
    if (m_rotation > 2 * 3.14159)
    {
        m_rotation = 0;
    }

    m_cameraDelta += 0.02;
    if (m_cameraDelta > 1)
    {
        m_cameraDelta = 0;
    }

    float fov = 90.0f * 3.14159 / 180.0f;
    float aspect_ratio = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;

    // these get mapped into the -1 to 1 range
    // the rasterizer then controls which z values are visible
    float zfar = 10.0;
    float znear = 1.0;

    float a = -1 - ((2 * zfar * znear) / (znear - zfar));
    float b = (2 * znear * zfar) / (znear - zfar);

    Vector3f cameraPosition(0, 0, m_cameraDelta);
    Vector3f U(1, 0, 0);
    Vector3f V(0, 1, 0);
    Vector3f N(0, 0, 1);

    Matrix4f worldToCameraProjection(
        U.x, U.y, U.z, -cameraPosition.x,
        V.x, V.y, V.z, -cameraPosition.y,
        N.x, N.y, N.z, -cameraPosition.z,
        0, 0, 0, 1);

    m_perspectiveProjection = Matrix4f(1 / aspect_ratio * tanf((fov / 2.0f)), 0, 0, 0,
                                       0, 1 / tanf(fov / 2.0f), 0, 0,
                                       0, 0, a, b,
                                       0, 0, 1, 0);

    Matrix4f translation(1, 0, 0, 0,
                         0, 1, 0, 0,
                         0, 0, 1, 3,
                         0, 0, 0, 1);

    Matrix4f transformation = m_perspectiveProjection * worldToCameraProjection * translation *
                              Matrix4f(cosf(m_rotation), 0, -sinf(m_rotation), 0,
                                       0, 1, 0, 0,
                                       sinf(m_rotation), 0, cosf(m_rotation), 0,
                                       0, 0, 0, 1);

    glUniformMatrix4fv(m_transformationLocation, 1, GL_TRUE, &transformation.matrix[0][0]);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void *)(sizeof(float) * 3));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}