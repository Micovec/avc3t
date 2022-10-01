#pragma once

#include <memory>
#include <unordered_map>

#include "LibraryRecordNames.h"

#include "../render/Shader.h"

namespace AVC3T {
    class ShaderLibrary {
      public:
        ShaderLibrary(const ShaderLibrary& other)                            = delete;
        void                           operator=(const ShaderLibrary& other) = delete;

        static ShaderLibrary&          GetInstance();

        static void                    Init();
        static void                    Deinit();
        static void                    CompileShader(const std::string& name, const std::string& filename);
        static std::shared_ptr<Shader> GetShader(const std::string& name);

      private:
        ShaderLibrary() : m_Shaders() {}

        std::unordered_map<std::string, std::shared_ptr<Shader>> m_Shaders;
    };
}