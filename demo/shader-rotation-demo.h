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

    Triangle m_triangle1;
    Triangle m_triangle2;
    GLuint m_vertexShaderObject;
    GLuint m_fragmentShaderObject;
    GLuint m_shaderProgram;
    GLint m_rotationLocation;
    GLint m_translationLocation;
    GLint m_translation2Location;

public:
    static ShaderRotationDemo *Instance(void);
    void Init(void);
    void Render(void);

private:
    void DrawTriangle(Triangle &triangle);
    void compile_shaders(GLuint *shaderProgram, GLuint *vertexShaderObject, GLuint *fragmentShaderObject);
    void add_shader(GLuint shaderProgram, GLuint *shaderObject, const char *pShaderText, GLenum shaderType);
};

#endif