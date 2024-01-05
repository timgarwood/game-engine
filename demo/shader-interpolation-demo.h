#ifndef _SHADER_INTERPOLATION_DEMO_H
#define _SHADER_INTERPOLATION_DEMO_H

#include "math.h"
#include <gl/glew.h>
#include <gl/gl.h>
#include <gl/glu.h>

class ShaderInterpolationDemo
{
private:
    static ShaderInterpolationDemo *s_instance;
    ShaderInterpolationDemo();

    Vector3f m_vertices[3];
    GLuint m_vbo;
    GLuint m_vertexShaderObject;
    GLuint m_fragmentShaderObject;
    GLuint m_shaderProgram;

public:
    static ShaderInterpolationDemo *Instance(void);
    void Init(void);
    void Render(void);

private:
    void compile_shaders(GLuint *shaderProgram, GLuint *vertexShaderObject, GLuint *fragmentShaderObject);
    void add_shader(GLuint shaderProgram, GLuint *shaderObject, const char *pShaderText, GLenum shaderType);
};

#endif