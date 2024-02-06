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
#include "camera.h"
#include "sdl-event-dispatcher.h"
#include "cube.h"

using namespace std;

vector<Quad3d> s_cubes;

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
    m_windowWidth = 640;
    m_windowHeight = 480;

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

static void perspective_projection_window_resized(int windowWidth, int windowHeight)
{
    PerspectiveProjectionDemo::Instance()->WindowResized(windowWidth, windowHeight);
}

void PerspectiveProjectionDemo::Init(void)
{
    s_cubes = vector<Quad3d>();
    s_cubes.push_back(Cube(Vector3f(0, 1, 0), 1, RAND_COLOR));
    s_cubes.push_back(Cube(Vector3f(5, 1, 1), 1, RAND_COLOR));
    s_cubes.push_back(Cube(Vector3f(-5, 1, 1), 1, RAND_COLOR));
    s_cubes.push_back(Cube(Vector3f(0, 1, 5), 1, RAND_COLOR));
    s_cubes.push_back(Cube(Vector3f(5, 1, 5), 1, RAND_COLOR));
    s_cubes.push_back(Cube(Vector3f(-5, 1, 5), 1, RAND_COLOR));

    //floor
    s_cubes.push_back(Quad3d(Vector3f(0, 0, 0), 10, .2, 10, RAND_COLOR));
    SDLEventDispatcher::Instance()->RegisterForWindowResized(perspective_projection_window_resized);
    ShaderFactory::Instance()->LoadShaders("./demo/perspective-projection-demo-shaders.json");
    m_shaderProgram = ShaderFactory::Instance()->GetShaderProgram("main");

    time_t t;
    srand((unsigned)time(&t));

    m_delta = 0.04f;
    m_rotation = 0.0f;

    auto cubeIter = s_cubes.begin();
    int vertexOffset = 0;
    for (; cubeIter != s_cubes.end(); ++cubeIter)
    {
        vector<Vertex3f> v = cubeIter->GetVertices();
        m_vertices.insert(m_vertices.end(), v.begin(), v.end());

        vector<int> i = cubeIter->GetIndices();

        auto indexIter = i.begin();
        for (; indexIter != i.end(); ++indexIter)
        {
            (*indexIter) += vertexOffset;
            m_indices.push_back(*indexIter);
        }

        vertexOffset += v.size();
    }

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex3f), &m_vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &m_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(int), &m_indices[0], GL_STATIC_DRAW);

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

    float fov = 65.0f * 3.14159 / 180.0f;
    float aspect_ratio = (float)m_windowHeight / (float)m_windowWidth;

    // these get mapped into the -1 to 1 range
    // the rasterizer then controls which z values are visible
    float zfar = 100.0;
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

    m_perspectiveProjection = Matrix4f(1.0f / tanf(fov / 2.0f), 0, 0, 0,
                                       0, 1 / (tanf(fov / 2.0f) * aspect_ratio), 0, 0,
                                       0, 0, a, b,
                                       0, 0, 1, 0);

    Matrix4f translation(1, 0, 0, 0,
                         0, 1, 0, 0,
                         0, 0, 1, 5,
                         0, 0, 0, 1);

    Matrix4f transformation = m_perspectiveProjection * Camera::Instance()->GetMatrix() * translation; // *
                                                                                                       // Matrix4f(cosf(m_rotation), 0, -sinf(m_rotation), 0,
                                                                                                       //        0, 1, 0, 0,
                                                                                                       //        sinf(m_rotation), 0, cosf(m_rotation), 0,
                                                                                                       //         0, 0, 0, 1);

    glUniformMatrix4fv(m_transformationLocation, 1, GL_TRUE, &transformation.matrix[0][0]);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void *)(sizeof(float) * 3));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

    glDrawElements(GL_TRIANGLES, 12 * 3 * s_cubes.size(), GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void PerspectiveProjectionDemo::WindowResized(int windowWidth, int windowHeight)
{
    m_windowWidth = windowWidth;
    m_windowHeight = windowHeight;
}