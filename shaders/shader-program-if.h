#ifndef _SHADER_PROGRAM_IF_H
#define _SHADER_PROGRAM_IF_H

#include <string>

class ShaderProgramIF
{
public:
    virtual void Enable() = 0;
    virtual int GetUniformLocation(const std::string &uniformName) = 0;
};

#endif