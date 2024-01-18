#include <gl/glew.h>
#include "shader-program.h"

using namespace std;

ShaderProgram::ShaderProgram(GLuint id)
{
    m_id = id;
}

void ShaderProgram::Enable()
{
    glUseProgram(m_id);
}

int ShaderProgram::GetUniformLocation(const string &uniformName)
{
    return (int)glGetUniformLocation(m_id, uniformName.c_str());
}