#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include "shader-translation-demo.h"
#include "graphics-engine.h"
#include "engine.h"
#include <stddef.h>
#include <iostream>
#include <cstring>

using namespace std;

void ShaderTranslationDemo::add_shader(GLuint shaderProgram, GLuint *shaderObject, const char *pShaderText, GLenum shaderType)
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

void ShaderTranslationDemo::compile_shaders(GLuint *shaderProgram, GLuint *vertexShaderObject, GLuint *fragmentShaderObject)
{
    *shaderProgram = glCreateProgram();

    if (*shaderProgram == 0)
    {

        cerr << "Error creating shader program" << endl;
        exit(1);
    }

    string vs = "#version 330 core\nlayout(location = 0) in vec3 Position;\nuniform mat4 gTranslation;\nvoid main()\n{\ngl_Position = gTranslation * vec4(Position, 1.0);\n}\n";
    string fs = "#version 330 core\nout vec4 FragColor;\nvoid main()\n{\nFragColor = vec4(1.0,0.0,0.0,0.0);\n}";

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

    m_translationLocation = glGetUniformLocation(*shaderProgram, "gTranslation");
    if (m_translationLocation == -1)
    {
        cout << "Error getting uniform location of 'gTranslation'" << endl;
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

ShaderTranslationDemo *ShaderTranslationDemo::s_instance = NULL;

static void init(void)
{
    ShaderTranslationDemo::Instance()->Init();
}

static void render(void)
{
    ShaderTranslationDemo::Instance()->Render();
}

ShaderTranslationDemo::ShaderTranslationDemo()
{
    Engine::Instance()->RegisterModuleInitCallback(init);
    GraphicsEngine::Instance()->RegisterRenderCallback(render);
}

ShaderTranslationDemo *ShaderTranslationDemo::Instance(void)
{
    if (s_instance == NULL)
    {
        s_instance = new ShaderTranslationDemo();
    }

    return s_instance;
}

void ShaderTranslationDemo::Init(void)
{
    m_translation = 0.0f;
    m_delta = 0.04f;
    m_vertices[0] = Vector3f(0.0f, 0.0f, 0.0f);
    m_vertices[1] = Vector3f(0.5f, 0.5f, 0.0f);
    m_vertices[2] = Vector3f(0.5f, 0.0f, 0.0f);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

    compile_shaders(&m_shaderProgram, &m_vertexShaderObject, &m_fragmentShaderObject);
}

void ShaderTranslationDemo::Render(void)
{
    if (m_translation >= .4f && m_delta > 0)
    {
        m_delta = -0.04f;
    }
    else if (m_translation <= 0 && m_delta < 0)
    {
        m_delta = 0.04f;
    }

    m_translation += m_delta;

    Matrix4f translation(1, 0, 0, m_translation,
                         0, 1, 0, m_translation,
                         0, 0, 1, 0,
                         0, 0, 0, 1);

    glUniformMatrix4fv(m_translationLocation, 1, GL_TRUE, &translation.matrix[0][0]);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(0);
}