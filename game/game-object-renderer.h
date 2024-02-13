#ifndef _GAME_OBJECT_RENDERER_H
#define _GAME_OBJECT_RENDERER_H

#include <vector>
#include "vector.h"
#include <memory>
#include "shader-program-if.h"

class GameObjectRenderer
{
public:
    static GameObjectRenderer *Instance();
    void Render();
    void Init();

private:
    GameObjectRenderer();
    static GameObjectRenderer *instance;
    GLuint m_staticVbo;
    GLuint m_staticIbo;
    GLuint m_dynamicVbo;
    GLuint m_dynamicIbo;
    std::vector<Vector3f> m_staticVertices;
    std::vector<int> m_staticIndices;

    std::shared_ptr<ShaderProgramIF> m_shaderProgram;
    GLuint m_viewLocation;
    GLuint m_transformationLocation;
    GLuint m_startTransformLocation;
    GLuint m_rotationLocation;
    GLuint m_colorLocation;
};

#endif