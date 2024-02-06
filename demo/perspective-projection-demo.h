#ifndef _PERSPECTIVE_PROJECTION_DEMO_H
#define _PERSPECTIVE_PROJECTION_DEMO_H

#include "math.h"
#include <gl/glew.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <memory>
#include <vector>

class ShaderProgramIF;

class PerspectiveProjectionDemo
{
private:
    static PerspectiveProjectionDemo *s_instance;
    PerspectiveProjectionDemo();

    std::vector<Vertex3f> m_vertices;
    std::vector<int> m_indices;
    GLuint m_vbo;
    GLuint m_ibo;
    GLuint m_vertexShaderObject;
    GLuint m_fragmentShaderObject;
    float m_delta;
    float m_rotation;
    Matrix4f m_perspectiveProjection;
    GLuint m_transformationLocation;
    std::shared_ptr<ShaderProgramIF> m_shaderProgram;

public:
    static PerspectiveProjectionDemo *Instance(void);
    void Init(void);
    void Render(void);
    void WindowResized(int windowWidth, int windowHeight);

    int m_windowWidth;
    int m_windowHeight;
};

#endif