#ifndef _SHADER_PARSER_H
#define _SHADER_PARSER_H

#include "shader-definition.h"
#include <vector>
#include <string.h>

class ShaderParser
{
public:
    std::vector<ShaderProgramDefinition> ParseShaderDefinitions(const std::string &filename);
};

#endif