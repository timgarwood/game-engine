#ifndef _SHADER_DEFINITION_H
#define _SHADER_DEFINITION_H

#include <string>
#include <vector>

typedef struct
{
    std::string shaderFile;
    std::string shaderType;
} ShaderDefinition;

typedef struct
{
    std::string name;
    std::vector<ShaderDefinition> shaders;
} ShaderProgramDefinition;

#endif