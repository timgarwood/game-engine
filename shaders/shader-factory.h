#ifndef _SHADER_FACTORY_H
#define _SHADER_FACTORY_H

#include "shader-factory-if.h"
#include <map>

class ShaderFactory : public ShaderFactoryIF
{
public:
    static ShaderFactoryIF *Instance();
    virtual void LoadShaders(const std::string &filename);
    virtual std::shared_ptr<ShaderProgramIF> GetShaderProgram(const std::string &name);
    virtual std::shared_ptr<ShaderIF> GetShader(const std::string &name);

private:
    std::map<std::string, std::shared_ptr<ShaderProgramIF>> m_shaderPrograms;
    static ShaderFactoryIF *s_instance;
};

#endif
