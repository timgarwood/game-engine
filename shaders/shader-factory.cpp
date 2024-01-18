#include <gl/glew.h>
#include "shader-factory.h"
#include "shader-parser.h"
#include "shader-program.h"
#include "file-utils.h"
#include <iostream>
#include <gl/gl.h>
#include <gl/glu.h>
#include <exception>

using namespace std;

ShaderFactoryIF *ShaderFactory::s_instance = NULL;

ShaderFactoryIF *ShaderFactory::Instance()
{
    if (s_instance == NULL)
    {
        s_instance = new ShaderFactory();
    }

    return s_instance;
}

void ShaderFactory::LoadShaders(const std::string &filename)
{
    ShaderParser shaderParser;
    vector<ShaderProgramDefinition> shaderProgramDefs = shaderParser.ParseShaderDefinitions(filename);

    for (int programIndex = 0; programIndex < shaderProgramDefs.size(); ++programIndex)
    {
        GLuint shaderProgramId = glCreateProgram();
        if (shaderProgramId == 0)
        {
            throw string("Error creating shader program");
        }

        shared_ptr<ShaderProgramIF> shaderProgram = make_shared<ShaderProgram>(shaderProgramId); //(new ShaderProgram(shaderProgramId));

        for (int shaderIndex = 0; shaderIndex < shaderProgramDefs[programIndex].shaders.size(); ++shaderIndex)
        {
            auto shaderDef = shaderProgramDefs[programIndex].shaders[shaderIndex];
            string shaderCode;
            read_file(shaderCode, shaderDef.shaderFile.c_str());

            GLenum shaderType;

            if (shaderDef.shaderType == "fragment")
            {
                shaderType = GL_FRAGMENT_SHADER;
            }
            else if (shaderDef.shaderType == "vertex")
            {
                shaderType = GL_VERTEX_SHADER;
            }
            else
            {
                string msg = "Invalid shader type: " + shaderDef.shaderType;
                throw msg;
            }

            GLuint shaderId = glCreateShader(shaderType);

            if (shaderId == 0)
            {
                string msg = "Error creating shader type " + shaderType;
                throw msg;
            }

            const GLchar *p[1];
            p[0] = shaderCode.c_str();

            GLint lengths[1];
            lengths[0] = shaderCode.length();

            glShaderSource(shaderId, 1, p, lengths);

            glCompileShader(shaderId);

            GLint success;
            glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

            if (!success)
            {
                throw string("Error compiling shader");
            }

            glAttachShader(shaderProgramId, shaderId);
        }

        GLint success = 0;

        glLinkProgram(shaderProgramId);

        glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &success);
        if (!success)
        {
            GLchar errorLog[1024] = {0};
            glGetProgramInfoLog(shaderProgramId, sizeof(errorLog), NULL, errorLog);
            cerr << errorLog << endl;
            throw string("Error linking shader");
        }

        glValidateProgram(shaderProgramId);
        glGetProgramiv(shaderProgramId, GL_VALIDATE_STATUS, &success);
        if (!success)
        {
            throw string("Error validating shader");
        }

        m_shaderPrograms[shaderProgramDefs[programIndex].name] = shaderProgram;
    }
}

shared_ptr<ShaderProgramIF> ShaderFactory::GetShaderProgram(const std::string &name)
{
    return m_shaderPrograms[name];
}

shared_ptr<ShaderIF> ShaderFactory::GetShader(const std::string &name)
{
    return shared_ptr<ShaderIF>();
}