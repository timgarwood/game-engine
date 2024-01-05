#ifndef _INDEX_BUFFER_DEMO_H
#define _INDEX_BUFFER_DEMO_H

#include "math.h"
#include <gl/glew.h>
#include <gl/gl.h>
#include <gl/glu.h>

class IndexBufferDemo
{
private:
    static IndexBufferDemo *s_instance;
    IndexBufferDemo();

    Vector3f m_vertices[9];
    Vector3i m_indexes[3 * 6]; // 6 triangles
    GLuint m_vbo;
    GLuint m_ibo;
    GLuint m_vertexShaderObject;
    GLuint m_fragmentShaderObject;
    GLuint m_shaderProgram;

public:
    static IndexBufferDemo *Instance(void);
    void Init(void);
    void Render(void);

private:
    void compile_shaders(GLuint *shaderProgram, GLuint *vertexShaderObject, GLuint *fragmentShaderObject);
    void add_shader(GLuint shaderProgram, GLuint *shaderObject, const char *pShaderText, GLenum shaderType);
};

#endif