#ifndef _SHADER_PROGRAM_H
#define _SHADER_PROGRAM_H

#include "shader-program-if.h"
#include <gl/gl.h>

class ShaderProgram : public ShaderProgramIF
{
public:
    ShaderProgram(GLuint id);
    virtual void Enable();
    virtual int GetUniformLocation(const std::string &uniformName);

private:
    GLuint m_id;
};

#endif