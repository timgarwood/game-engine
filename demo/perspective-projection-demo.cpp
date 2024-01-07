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

using namespace std;

float max_color = 255.0f;
#define RAND_COLOR Vector3f((float)(rand() % 255) / max_color, (float)(rand() % 255) / max_color, (float)(rand() % 255) / max_color)

void PerspectiveProjectionDemo::add_shader(GLuint shaderProgram, GLuint *shaderObject, const char *pShaderText, GLenum shaderType)
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

void PerspectiveProjectionDemo::compile_shaders(GLuint *shaderProgram, GLuint *vertexShaderObject, GLuint *fragmentShaderObject)
{
    *shaderProgram = glCreateProgram();

    if (*shaderProgram == 0)
    {

        cerr << "Error creating shader program" << endl;
        exit(1);
    }

    string vs, fs;
    read_file(vs, "./demo/perspective-projection-demo.vs");
    read_file(fs, "./demo/perspective-projection-demo.fs");

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

void PerspectiveProjectionDemo::Init(void)
{
    time_t t;
    srand((unsigned)time(&t));

    m_delta = 0.04f;
    m_rotation = 0.0f;

    m_perspectiveProjection = Matrix4f(1, 0, 0, 0,
                                       0, 1, 0, 0,
                                       0, 0, 1, 0,
                                       0, 0, 0, 1);

    float fov = 90.0f * 3.14159 / 180.0f;
    m_perspectiveProjection = Matrix4f(1 / tanf(fov / 2.0f), 0, 0, 0,
                                       0, 1 / tanf(fov / 2.0f), 0, 0,
                                       0, 0, 1, 0,
                                       0, 0, 1, 0);

    m_vertices[0] = Vertex3f(Vector3f(0.5f, 0.5f, 0.5f), RAND_COLOR);
    m_vertices[1] = Vertex3f(Vector3f(-0.5f, 0.5f, -0.5f), RAND_COLOR);
    m_vertices[2] = Vertex3f(Vector3f(-0.5f, 0.5f, 0.5f), RAND_COLOR);
    m_vertices[3] = Vertex3f(Vector3f(0.5f, -0.5f, -0.5f), RAND_COLOR);
    m_vertices[4] = Vertex3f(Vector3f(-0.5f, -0.5f, -0.5f), RAND_COLOR);
    m_vertices[5] = Vertex3f(Vector3f(0.5f, 0.5f, -0.5f), RAND_COLOR);
    m_vertices[6] = Vertex3f(Vector3f(0.5f, -0.5f, 0.5f), RAND_COLOR);
    m_vertices[7] = Vertex3f(Vector3f(-0.5f, -0.5f, 0.5f), RAND_COLOR);

    m_indexes[0] = Vector3i(0, 1, 2);
    m_indexes[1] = Vector3i(1, 3, 4);
    m_indexes[2] = Vector3i(5, 6, 3);
    m_indexes[3] = Vector3i(7, 3, 6);
    m_indexes[4] = Vector3i(2, 4, 7);
    m_indexes[5] = Vector3i(0, 7, 6);
    m_indexes[6] = Vector3i(0, 5, 1);
    m_indexes[7] = Vector3i(1, 5, 3);
    m_indexes[8] = Vector3i(5, 0, 6);
    m_indexes[9] = Vector3i(7, 4, 3);
    m_indexes[10] = Vector3i(2, 1, 4);
    m_indexes[11] = Vector3i(0, 2, 7);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &m_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indexes), m_indexes, GL_STATIC_DRAW);

    compile_shaders(&m_shaderProgram, &m_vertexShaderObject, &m_fragmentShaderObject);

    m_transformationLocation = glGetUniformLocation(m_shaderProgram, "gTransformation");
}

void PerspectiveProjectionDemo::Render(void)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    m_rotation += m_delta;
    if (m_rotation > 2 * 3.14159)
    {
        m_rotation = 0;
    }

    Matrix4f translation(1, 0, 0, -0.4,
                         0, 1, 0, 0.8,
                         0, 0, 1, 3,
                         0, 0, 0, 1);

    Matrix4f transformation = m_perspectiveProjection.multiply(
        translation.multiply(Matrix4f(cosf(m_rotation), 0, -sinf(m_rotation), 0,
                                      0, 1, 0, 0,
                                      sinf(m_rotation), 0, cosf(m_rotation), 0,
                                      0, 0, 0, 1)));

    glUniformMatrix4fv(m_transformationLocation, 1, GL_TRUE, &transformation.matrix[0][0]);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void *)(sizeof(float) * 3));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}