#include "shader-parser.h"
#include "file-utils.h"
#include <fstream>
#include "json/json.h"

using namespace std;

vector<ShaderProgramDefinition> ShaderParser::ParseShaderDefinitions(const string &filename)
{
    ifstream fileStream(filename.c_str());
    vector<ShaderProgramDefinition> defs;
    if (!fileStream.is_open())
    {
        // TODO throw
    }

    Json::Value rootNode;

    fileStream >> rootNode;

    Json::Value programs = rootNode["programs"];

    int numPrograms = int(programs.size());

    for (int i = 0; i < numPrograms; ++i)
    {
        Json::Value program = programs[i];

        ShaderProgramDefinition programDef;
        programDef.name = program["name"].asString();

        Json::Value shaders = program["shaders"];
        int numShaders = int(shaders.size());
        for (int j = 0; j < numShaders; ++j)
        {
            Json::Value shader = shaders[j];
            ShaderDefinition shaderDef;
            shaderDef.shaderType = shader["type"].asString();
            shaderDef.shaderFile = shader["file"].asString();

            programDef.shaders.push_back(shaderDef);
        }

        defs.push_back(programDef);
    }

    return defs;
}