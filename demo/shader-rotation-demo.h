#ifndef _SHADER_TRANSLATION_DEMO_H
#define _SHADER_TRANSLATION_DEMO_H

#include "math.h"
#include <gl/glew.h>
#include <gl/gl.h>
#include <gl/glu.h>

class ShaderRotationDemo
{
private:
    static ShaderRotationDemo *s_instance;
    ShaderRotationDemo();

    Vector3f m_vertices[3];
    GLuint m_vbo;
    GLuint m_vertexShaderObject;
    GLuint m_fragmentShaderObject;
    GLuint m_shaderProgram;
    GLint m_rotationLocation;
    float m_delta;
    float m_rotation;

public:
    static ShaderRotationDemo *Instance(void);
    void Init(void);
    void Render(void);

private:
    void compile_shaders(GLuint *shaderProgram, GLuint *vertexShaderObject, GLuint *fragmentShaderObject);
    void add_shader(GLuint shaderProgram, GLuint *shaderObject, const char *pShaderText, GLenum shaderType);
};

#endif