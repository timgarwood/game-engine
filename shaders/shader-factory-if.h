#ifndef _SHADER_FACTORY_IF_H
#define _SHADER_FACTORY_IF_H

#include <memory>

class ShaderProgramIF;
class ShaderIF;

class ShaderFactoryIF
{
public:
    virtual void LoadShaders(const std::string &filename) = 0;
    virtual std::shared_ptr<ShaderProgramIF> GetShaderProgram(const std::string &name) = 0;
    virtual std::shared_ptr<ShaderIF> GetShader(const std::string &name) = 0;
};

#endif
