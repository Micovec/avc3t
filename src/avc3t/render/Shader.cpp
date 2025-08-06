#include "Shader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <glm/gtc/type_ptr.hpp>

#include "../utils/Macros.h"

namespace AVC3T {
    Shader::Shader(const std::string& filepath) : m_FilePath(filepath), m_RendererID(0), m_UniformLocationCache() {
        ShaderProgramSource source = ParseShader(filepath);
        m_RendererID               = CreateShader(source.VertexSource, source.FragmentSource);
    }

    Shader::~Shader() {
        GLCall(glDeleteProgram(m_RendererID));
    }

    ShaderProgramSource Shader::ParseShader(const std::string& filepath) {
        // std::ifstream stream(filepath);
        std::stringstream stream(R"(#shader vertex
#version 300 es

//layout(location = 0) out vec4 color;
//
////in vec2 v_TexCoord;
//
//uniform vec4 u_Color;
////uniform sampler2D u_Texture;
//
//void main()
//{
//	//vec4 texColor = texture(u_Texture, v_TexCoord);
//	color = u_Color;
//};

in vec3 i_Position;
in vec3 i_Normal;
in vec2 i_Uv;

uniform mat4 u_MVP;
uniform mat4 u_ViewMatrix;
uniform mat4 u_NormalMatrix;

smooth out vec2 v_uv;
out vec3 v_Normal;

void main()
{
            gl_Position = u_MVP * vec4(i_Position, 1);

            v_uv     = i_Uv;
            v_Normal = normalize((u_ViewMatrix * u_NormalMatrix * vec4(i_Normal, 0)).xyz); // Normal in eye coords
}

#shader fragment
#version 300 es

precision highp float;
precision highp sampler2D;

struct Material
{
            vec3 ambient;
            vec3 diffuse;

            // Texture
            sampler2D diffuseSampler;
};

struct Light
{
            // Color changing variables
            vec3 ambient;
            vec3 diffuse;

            // Transform
            vec3 direction;
};

uniform Material u_Material;
uniform mat4 u_ViewMatrix;

// Lights
uniform Light u_DirectionalLight;

smooth in vec2 v_uv;		// Texture position
in vec3 v_Normal;	// Eye space coord

out vec4 o_Color;

// Method definition
vec4 calculateLight(vec3 lightVector, vec3 vertexNormal, Material material, Light light);
vec4 directionalLight(vec3 vertexNormal, Material material, Light light);

void main()
{
            vec4 finalColor = directionalLight(v_Normal, u_Material, u_DirectionalLight);

            o_Color = finalColor;
}

vec4 calculateLight(vec3 lightVector, vec3 vertexNormal, Material material, Light light)
{
            vec4 materialDiffuseTex = texture(material.diffuseSampler, v_uv);

            // Ambient
            vec4 ambient = vec4(light.ambient * material.ambient.rgb, 1);

            // Diffuse
            vec3 normal = normalize(vertexNormal);
            //vec3 normal = normalize(vec3(1,1,0));

            float diff    = max(dot(normal, lightVector), 0.0);
            vec4  diffuse = vec4(light.diffuse * material.diffuse.rgb, 1) * diff;

            return (ambient + diffuse) * materialDiffuseTex;
}

vec4 directionalLight(vec3 vertexNormal, Material material, Light light)
{
            vec3 lightDirection = normalize(mat3(u_ViewMatrix) * light.direction);
            return calculateLight(lightDirection, vertexNormal, material, light);
}

// -----------------------------------------------------
        )");

        enum class ShaderType {
            NONE     = -1,
            VERTEX   = 0,
            FRAGMENT = 1
        };

        std::string       line;
        std::stringstream ss[2];
        ShaderType        type = ShaderType::NONE;
        while (getline(stream, line)) {
            if (line.find("#shader") != std::string::npos) {
                if (line.find("vertex") != std::string::npos)
                    type = ShaderType::VERTEX;
                else if (line.find("fragment") != std::string::npos)
                    type = ShaderType::FRAGMENT;
            } else {
                ss[(int)type] << line << '\n';
            }
        }

        return {ss[0].str(), ss[1].str()};
    }

    unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
        GLCall(unsigned int id = glCreateShader(type));
        const char* src = source.c_str();
        GLCall(glShaderSource(id, 1, &src, nullptr));
        GLCall(glCompileShader(id));

        int result;
        GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
        if (result == GL_FALSE) {
            int length;
            GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
            char* message = (char*)alloca(length * sizeof(char));
            GLCall(glGetShaderInfoLog(id, length, &length, message));
            std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
            std::cout << message << std::endl;
            std::cout << "Shader:" << std::endl;
            std::cout << source << std::endl;
            GLCall(glDeleteShader(id));
            return 0;
        }

        return id;
    }

    unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
        GLCall(unsigned int program = glCreateProgram());
        unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
        unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

        GLCall(glAttachShader(program, vs));
        GLCall(glAttachShader(program, fs));
        GLCall(glLinkProgram(program));
        GLCall(glValidateProgram(program));

        GLCall(glDeleteShader(vs));
        GLCall(glDeleteShader(fs));

        return program;
    }

    void Shader::Bind() const {
        GLCall(glUseProgram(m_RendererID));
    }

    void Shader::Unbind() const {
        GLCall(glUseProgram(0));
    }

    void Shader::SetUniform1i(const std::string& name, int value) {
        GLCall(glUniform1i(GetUniformLocation(name), value));
    }

    void Shader::SetUniform1f(const std::string& name, float value) {
        GLCall(glUniform1f(GetUniformLocation(name), value));
    }

    void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
        GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
    }

    void Shader::SetUniformVec3(const std::string& name, const glm::vec3& vec) {
        GLCall(glUniform3fv(GetUniformLocation(name), 1, glm::value_ptr(vec)));
    }

    void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix) {
        GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
    }

    int Shader::GetUniformLocation(const std::string& name) {
        auto cacheLocation = m_UniformLocationCache.find(name);
        if (cacheLocation != m_UniformLocationCache.end())
            return cacheLocation->second;

        GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
        if (location == -1)
            std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;

        m_UniformLocationCache[name] = location;
        return location;
    }
}