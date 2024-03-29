#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include "shader-rotation-demo.h"
#include "graphics-engine.h"
#include "engine.h"
#include <stddef.h>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

void ShaderRotationDemo::add_shader(GLuint shaderProgram, GLuint *shaderObject, const char *pShaderText, GLenum shaderType)
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

void ShaderRotationDemo::compile_shaders(GLuint *shaderProgram, GLuint *vertexShaderObject, GLuint *fragmentShaderObject)
{
    *shaderProgram = glCreateProgram();

    if (*shaderProgram == 0)
    {

        cerr << "Error creating shader program" << endl;
        exit(1);
    }

    string vs = "#version 330 core\nlayout(location = 0) in vec3 Position;\nuniform mat4 gRotation;\nuniform mat4 gTranslation;\nuniform mat4 gTranslation2;\nvoid main()\n{\ngl_Position = gTranslation2 * gRotation * gTranslation * vec4(Position, 1.0);\n}\n";
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

    m_rotationLocation = glGetUniformLocation(*shaderProgram, "gRotation");
    m_translationLocation = glGetUniformLocation(*shaderProgram, "gTranslation");
    m_translation2Location = glGetUniformLocation(*shaderProgram, "gTranslation2");
    if (m_rotationLocation == -1)
    {
        cout << "Error getting uniform location of 'gRotation'" << endl;
        exit(1);
    }
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

ShaderRotationDemo *ShaderRotationDemo::s_instance = NULL;

static void init(void)
{
    ShaderRotationDemo::Instance()->Init();
}

static void render(void)
{
    ShaderRotationDemo::Instance()->Render();
}

ShaderRotationDemo::ShaderRotationDemo()
{
    Engine::Instance()->RegisterModuleInitCallback(init);
    GraphicsEngine::Instance()->RegisterRenderCallback(render);
}

ShaderRotationDemo *ShaderRotationDemo::Instance(void)
{
    if (s_instance == NULL)
    {
        s_instance = new ShaderRotationDemo();
    }

    return s_instance;
}

void ShaderRotationDemo::Init(void)
{
    m_triangle1 = Triangle(Vector3f(0.0f, 0.0f, 0.0f),
                           Vector3f(0.5f, 0.0f, 0.0f),
                           Vector3f(0.5f, 0.5f, 0.0f));
    m_triangle1.rotation = 0.0f;
    m_triangle1.rotationDelta = 0.1f;

    m_triangle1.translationMatrix = Matrix4f(1, 0, 0, -0.35,
                                             0, 1, 0, -0.125,
                                             0, 0, 1, 1,
                                             0, 0, 0, 1);

    m_triangle2 = Triangle(Vector3f(-0.5f, -0.5f, 0.0f),
                           Vector3f(0.0f, -0.5f, 0.0f),
                           Vector3f(0.0f, 0.0f, 0.0f));

    m_triangle2.rotation = 0.0f;
    m_triangle2.rotationDelta = -0.1f;

    m_triangle2.translationMatrix = Matrix4f(1, 0, 0, 0,
                                             0, 1, 0, 0,
                                             0, 0, 1, 1,
                                             0, 0, 0, 1);

    glGenBuffers(1, &m_triangle1.vbo);
    glGenBuffers(1, &m_triangle2.vbo);

    compile_shaders(&m_shaderProgram, &m_vertexShaderObject, &m_fragmentShaderObject);
}

void ShaderRotationDemo::DrawTriangle(Triangle &triangle)
{
    if (fabsf(triangle.rotation) >= 2 * 3.14159)
    {
        triangle.rotation = 0;
    }

    triangle.rotation += triangle.rotationDelta;

    triangle.rotationMatrix = Matrix4f(cosf(triangle.rotation), -sinf(triangle.rotation), 0, 0,
                                       sinf(triangle.rotation), cosf(triangle.rotation), 0, 0,
                                       0, 0, 1, 0,
                                       0, 0, 0, 1);

    glUniformMatrix4fv(m_rotationLocation, 1, GL_TRUE, &triangle.rotationMatrix.matrix[0][0]);
    glUniformMatrix4fv(m_translationLocation, 1, GL_TRUE, &triangle.translationMatrix.matrix[0][0]);
    glUniformMatrix4fv(m_translation2Location, 1, GL_TRUE, &triangle.translationMatrix2.matrix[0][0]);

    glBindBuffer(GL_ARRAY_BUFFER, m_triangle1.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle.vertices), triangle.vertices, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ShaderRotationDemo::Render(void)
{
    static float xoffset = 0.0f;
    xoffset += 0.001;
    m_triangle1.translationMatrix2.SetIdentity();
    m_triangle1.translationMatrix2.matrix[0][3] = xoffset;

    DrawTriangle(m_triangle1);
    //    DrawTriangle(m_triangle2);
}