#ifndef _PERSPECTIVE_PROJECTION_DEMO_H
#define _PERSPECTIVE_PROJECTION_DEMO_H

#include "math.h"
#include <gl/glew.h>
#include <gl/gl.h>
#include <gl/glu.h>

class PerspectiveProjectionDemo
{
private:
    static PerspectiveProjectionDemo *s_instance;
    PerspectiveProjectionDemo();

    Vertex3f m_vertices[8];
    Vector3i m_indexes[12];
    GLuint m_vbo;
    GLuint m_ibo;
    GLuint m_vertexShaderObject;
    GLuint m_fragmentShaderObject;
    GLuint m_shaderProgram;
    float m_delta;
    float m_rotation;
    Matrix4f m_perspectiveProjection;
    GLuint m_transformationLocation;

public:
    static PerspectiveProjectionDemo *Instance(void);
    void Init(void);
    void Render(void);

private:
    void compile_shaders(GLuint *shaderProgram, GLuint *vertexShaderObject, GLuint *fragmentShaderObject);
    void add_shader(GLuint shaderProgram, GLuint *shaderObject, const char *pShaderText, GLenum shaderType);
};

#endif