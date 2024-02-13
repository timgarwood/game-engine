#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include "engine.h"
#include "graphics-engine.h"
#include <stddef.h>
#include <iostream>
#include <cstring>
#include <time.h>
#include <cmath>
#include "shader-factory.h"
#include "shader-program.h"
#include "camera.h"
#include "sdl-event-dispatcher.h"

#include "game-object-renderer.h"
#include "game-world.h"
#include "game-object-if.h"

#include "btBulletDynamicsCommon.h"

using namespace std;

GameObjectRenderer *GameObjectRenderer::instance = NULL;

static void game_object_renderer_init()
{
    GameObjectRenderer::Instance()->Init();
}

static void game_object_renderer_render()
{
    GameObjectRenderer::Instance()->Render();
}

GameObjectRenderer *GameObjectRenderer::Instance()
{
    if (instance == NULL)
    {
        instance = new GameObjectRenderer();
    }

    return instance;
}

GameObjectRenderer::GameObjectRenderer()
{
    Engine::Instance()->RegisterModuleInitCallback(game_object_renderer_init);
    GraphicsEngine::Instance()->RegisterRenderCallback(game_object_renderer_render);
}

void GameObjectRenderer::Init()
{
    ShaderFactory::Instance()->LoadShaders("./demo/bullet-physics-demo-shaders.json");
    m_shaderProgram = ShaderFactory::Instance()->GetShaderProgram("main");

    vector<GameObjectIF *> statics = GameWorld::Instance()->GetStatics();
    auto iter = statics.begin();
    int vertexOffset = 0;
    for (; iter != statics.end(); ++iter)
    {
        GameObjectIF *gameObject = *iter;
        const vector<Vector3f> &gameObjectVertices = gameObject->GetVertices();
        const vector<int> &gameObjectIndice = gameObject->GetIndices();

        m_staticVertices.insert(m_staticVertices.end(), gameObjectVertices.begin(), gameObjectVertices.end());

        vector<int> gameObjectIndices = gameObject->GetIndices();

        auto indexIter = gameObjectIndices.begin();
        for (; indexIter != gameObjectIndices.end(); ++indexIter)
        {
            (*indexIter) += vertexOffset;
            m_staticIndices.push_back(*indexIter);
        }

        vertexOffset += gameObjectVertices.size();
    }

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);

    glGenBuffers(1, &m_staticVbo);
    glGenBuffers(1, &m_dynamicVbo);

    glBindBuffer(GL_ARRAY_BUFFER, m_staticVbo);

    glBufferData(GL_ARRAY_BUFFER, m_staticVertices.size() * sizeof(Vector3f), &m_staticVertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &m_staticIbo);
    glGenBuffers(1, &m_dynamicIbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_staticIbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_staticIndices.size() * sizeof(int), &m_staticIndices[0], GL_STATIC_DRAW);

    m_shaderProgram->Enable();

    m_viewLocation = (GLuint)m_shaderProgram->GetUniformLocation("gView");
    m_transformationLocation = (GLuint)m_shaderProgram->GetUniformLocation("gTransformation");
    m_startTransformLocation = (GLuint)m_shaderProgram->GetUniformLocation("gStartOffset");
    m_rotationLocation = (GLuint)m_shaderProgram->GetUniformLocation("gRotation");
    m_colorLocation = (GLuint)m_shaderProgram->GetUniformLocation("gColor");
}

void GameObjectRenderer::Render()
{
    float fov = 65.0f * 3.14159 / 180.0f;
    float aspect_ratio = 480.0 / 640.0;

    // these get mapped into the -1 to 1 range
    // the rasterizer then controls which z values are visible
    float zfar = 1000.0;
    float znear = 1.0;

    float a = -1 - ((2 * zfar * znear) / (znear - zfar));
    float b = (2 * znear * zfar) / (znear - zfar);

    Matrix4f perspectiveProjection = Matrix4f(1.0f / tanf(fov / 2.0f), 0, 0, 0,
                                              0, 1 / (tanf(fov / 2.0f) * aspect_ratio), 0, 0,
                                              0, 0, a, b,
                                              0, 0, 1, 0);

    Matrix4f translation(1, 0, 0, 0,
                         0, 1, 0, 20,
                         0, 0, 1, 15,
                         0, 0, 0, 1);

    Matrix4f view = perspectiveProjection * Camera::Instance()->GetMatrix() * translation;

    glBindBuffer(GL_ARRAY_BUFFER, m_staticVbo);

    Matrix4f staticTransformation;
    Matrix4f staticStartOffset;
    Matrix4f staticRotation;
    staticTransformation.SetIdentity();
    staticStartOffset.SetIdentity();
    staticRotation.SetIdentity();

    glUniformMatrix4fv(m_viewLocation, 1, GL_TRUE, &view.matrix[0][0]);
    glUniformMatrix4fv(m_transformationLocation, 1, GL_FALSE, &staticTransformation.matrix[0][0]);
    glUniformMatrix4fv(m_startTransformLocation, 1, GL_TRUE, &staticStartOffset.matrix[0][0]);
    glUniformMatrix4fv(m_rotationLocation, 1, GL_TRUE, &staticRotation.matrix[0][0]);
    float staticColor[3];
    staticColor[0] = 0;
    staticColor[1] = 0;
    staticColor[2] = 1;
    glUniform3fv(m_colorLocation, 1, staticColor);

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_staticIbo);

    glDrawElements(GL_TRIANGLES, 12 * 3 * m_staticVertices.size(), GL_UNSIGNED_INT, 0);

    //draw dynamic objects
    auto dynamics = GameWorld::Instance()->GetDynamics();
    auto iter = dynamics.begin();
    for (; iter != dynamics.end(); ++iter)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_dynamicVbo);

        const vector<Vector3f> &gameObjectVertices = (*iter)->GetVertices();
        const vector<int> &gameObjectIndices = (*iter)->GetIndices();

        glBufferData(GL_ARRAY_BUFFER, gameObjectVertices.size() * sizeof(Vector3f), &gameObjectVertices[0], GL_DYNAMIC_DRAW);

        Matrix4f startOffset = (*iter)->GetStartOffset();

        Matrix4f rotation = (*iter)->GetRotation();
        rotation.matrix[3][0] = 0;
        rotation.matrix[3][1] = 0;
        rotation.matrix[3][2] = 0;
        rotation.matrix[3][3] = 1;

        Vector3f vposition = (*iter)->GetPosition();

        Matrix4f position;
        position.SetIdentity();
        position.matrix[0][3] = vposition.x + startOffset.matrix[0][3];
        position.matrix[1][3] = vposition.y + startOffset.matrix[1][3];
        position.matrix[2][3] = vposition.z + startOffset.matrix[2][3];

        Matrix4f negStartOffset = startOffset;
        negStartOffset.matrix[0][3] *= -1;
        negStartOffset.matrix[1][3] *= -1;
        negStartOffset.matrix[2][3] *= -1;

        Matrix4f finalTransform = position * negStartOffset * rotation * startOffset;

        glUniformMatrix4fv(m_viewLocation, 1, GL_TRUE, &view.matrix[0][0]);
        glUniformMatrix4fv(m_transformationLocation, 1, GL_TRUE, &finalTransform.matrix[0][0]);
        Vector3f color = (*iter)->GetColor();
        float dynColor[3];
        dynColor[0] = color.x;
        dynColor[1] = color.y;
        dynColor[2] = color.z;
        glUniform3fv(m_colorLocation, 1, dynColor);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_dynamicIbo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, gameObjectIndices.size() * sizeof(int), &gameObjectIndices[0], GL_DYNAMIC_DRAW);

        glDrawElements(GL_TRIANGLES, 12 * 3 * gameObjectVertices.size(), GL_UNSIGNED_INT, 0);
    }

    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}