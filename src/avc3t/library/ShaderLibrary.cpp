#include "ShaderLibrary.h"

namespace AVC3T {
    ShaderLibrary& ShaderLibrary::GetInstance() {
        static ShaderLibrary library;

        return library;
    }

    void ShaderLibrary::CompileShader(const std::string& name, const std::string& filename) {
        GetInstance().m_Shaders.emplace(name, std::make_shared<Shader>(filename));
    }

    std::shared_ptr<Shader> ShaderLibrary::GetShader(const std::string& name) {
        auto shaders       = GetInstance().m_Shaders;
        auto libraryShader = shaders.find(name);

        if (libraryShader == shaders.end())
            return shaders[SHADER_DEFAULT_NAME];

        return libraryShader->second;
    }

    void ShaderLibrary::Init() {
        CompileShader(SHADER_DEFAULT_NAME, SHADER_DEFAULT_FILENAME);
        CompileShader(SHADER_LINES_NAME, SHADER_LINES_FILENAME);
    }

    void ShaderLibrary::Deinit() {
        GetInstance().m_Shaders.clear();
    }
}