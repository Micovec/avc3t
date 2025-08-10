#pragma once

#include <memory>
#include <unordered_map>

#include "LibraryRecordNames.h"

#include "../render/Shader.h"
#include "../io/MemoryIOSystem.h"

namespace AVC3T {
    class ShaderLibrary {
      public:
        ShaderLibrary(const ShaderLibrary& other)                            = delete;
        void                           operator=(const ShaderLibrary& other) = delete;

        static ShaderLibrary&          GetInstance();

        static void                    Init(MemoryIOSystem& memorySystem);
        static void                    Deinit();
        static void                    CompileShader(const std::string& name, const std::string& filename);
        static std::shared_ptr<Shader> GetShader(const std::string& name);

      private:
        ShaderLibrary() : m_Shaders() {}

        MemoryIOSystem*                                          m_MemoryIOSystem;
        std::unordered_map<std::string, std::shared_ptr<Shader>> m_Shaders;
    };
}