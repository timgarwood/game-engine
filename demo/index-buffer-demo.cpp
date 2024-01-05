#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include "index-buffer-demo.h"
#include "graphics-engine.h"
#include "engine.h"
#include <stddef.h>
#include <iostream>
#include <cstring>
#include "file-utils.h"

using namespace std;

void IndexBufferDemo::add_shader(GLuint shaderProgram, GLuint *shaderObject, const char *pShaderText, GLenum shaderType)
{
    *shaderObject = glCreateShader(shaderType);

    if (*shaderObject == 0)
    {
        cerr << "Error creating shader type " << shaderType << endl;
        exit(1);
    }

    const GLchar *p[1];
    p[0] = pShaderText;

    GLint lengths[1];
    lengths[0] = (GLint)strlen(pShaderText);

    glShaderSource(*shaderObject, 1, p, lengths);

    glCompileShader(*shaderObject);

    GLint success;
    glGetShaderiv(*shaderObject, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        GLchar infoLog[1024];
        glGetShaderInfoLog(*shaderObject, 1024, NULL, infoLog);
        cerr << "Error compiling shader type " << shaderType << ": " << infoLog << endl;
        exit(1);
    }

    glAttachShader(shaderProgram, *shaderObject);
}

void IndexBufferDemo::compile_shaders(GLuint *shaderProgram, GLuint *vertexShaderObject, GLuint *fragmentShaderObject)
{
    *shaderProgram = glCreateProgram();

    if (*shaderProgram == 0)
    {

        cerr << "Error creating shader program" << endl;
        exit(1);
    }

    string vs, fs;
    read_file(vs, "./demo/shader-interpolation-demo.vs");
    read_file(fs, "./demo/shader-interpolation-demo.fs");

    add_shader(*shaderProgram, vertexShaderObject, vs.c_str(), GL_VERTEX_SHADER);
    add_shader(*shaderProgram, fragmentShaderObject, fs.c_str(), GL_FRAGMENT_SHADER);

    GLint success = 0;
    GLchar errorLog[1024] = {0};

    glLinkProgram(*shaderProgram);

    glGetProgramiv(*shaderProgram, GL_LINK_STATUS, &success);
    if (success == 0)
    {
        glGetProgramInfoLog(*shaderProgram, sizeof(errorLog), NULL, errorLog);
        cerr << "Error linking shader program: " << errorLog << endl;
        exit(1);
    }

    glValidateProgram(*shaderProgram);
    glGetProgramiv(*shaderProgram, GL_VALIDATE_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(*shaderProgram, sizeof(errorLog), NULL, errorLog);
        cerr << "Invalid shader program: '" << errorLog << "'" << endl;
        exit(1);
    }

    glUseProgram(*shaderProgram);
}

IndexBufferDemo *IndexBufferDemo::s_instance = NULL;

static void init(void)
{
    IndexBufferDemo::Instance()->Init();
}

static void render(void)
{
    IndexBufferDemo::Instance()->Render();
}

IndexBufferDemo::IndexBufferDemo()
{
    Engine::Instance()->RegisterModuleInitCallback(init);
    GraphicsEngine::Instance()->RegisterRenderCallback(render);
}

IndexBufferDemo *IndexBufferDemo::Instance(void)
{
    if (s_instance == NULL)
    {
        s_instance = new IndexBufferDemo();
    }

    return s_instance;
}

void IndexBufferDemo::Init(void)
{
    m_vertices[0] = Vector3f(0.0f, 0.0f, 0.0f);
    m_vertices[1] = Vector3f(-0.5f, 0.5f, 0.0f);
    m_vertices[2] = Vector3f(-0.25f, 0.5f, 0.0f);
    m_vertices[3] = Vector3f(0.0f, 0.5f, 0.0f);
    m_vertices[4] = Vector3f(0.25f, 0.5f, 0.0f);
    m_vertices[5] = Vector3f(-0.5f, -0.5f, 0.0f);
    m_vertices[6] = Vector3f(-0.25f, -0.5f, 0.0f);
    m_vertices[7] = Vector3f(0.0f, -0.5f, 0.0f);
    m_vertices[8] = Vector3f(0.25f, 0.5f, 0.0f);

    m_indexes[0] = Vector3i(0, 2, 1);
    m_indexes[1] = Vector3i(0, 3, 2);
    m_indexes[2] = Vector3i(0, 4, 3);
    m_indexes[3] = Vector3i(5, 6, 0);
    m_indexes[4] = Vector3i(6, 7, 0);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &m_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indexes), m_indexes, GL_STATIC_DRAW);

    compile_shaders(&m_shaderProgram, &m_vertexShaderObject, &m_fragmentShaderObject);
}

void IndexBufferDemo::Render(void)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

    glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
}