#include "ShaderLibrary.h"
#include <iostream>

namespace AVC3T {
    ShaderLibrary& ShaderLibrary::GetInstance() {
        static ShaderLibrary library;

        return library;
    }

    void ShaderLibrary::CompileShader(const std::string& name, const std::string& filename) {
        ShaderLibrary&    instance   = GetInstance();
        const MemoryFile& memoryFile = instance.m_MemoryIOSystem->OpenFile(filename);

        instance.m_Shaders.emplace(name, std::make_shared<Shader>(memoryFile.GetText()));
    }

    std::shared_ptr<Shader> ShaderLibrary::GetShader(const std::string& name) {
        ShaderLibrary& instance = GetInstance();

        auto           shaders       = instance.m_Shaders;
        auto           libraryShader = shaders.find(name);

        if (libraryShader == shaders.end())
            return shaders[SHADER_DEFAULT_NAME];

        return libraryShader->second;
    }

    void ShaderLibrary::Init(MemoryIOSystem& memorySystem) {
        GetInstance().m_MemoryIOSystem = &memorySystem;

        CompileShader(SHADER_DEFAULT_NAME, SHADER_DEFAULT_FILENAME);
        CompileShader(SHADER_LINES_NAME, SHADER_LINES_FILENAME);
    }

    void ShaderLibrary::Deinit() {
        GetInstance().m_Shaders.clear();
    }
}