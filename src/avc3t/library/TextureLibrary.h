#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "../io/MemoryIOSystem.h"
#include "../render/Texture.h"

namespace AVC3T {
    class TextureLibrary {
      public:
        TextureLibrary(const TextureLibrary& other)                            = delete;
        void                            operator=(const TextureLibrary& other) = delete;

        static TextureLibrary&          GetInstance();

        static void                     Init(MemoryIOSystem& memoryIOSystem);
        static void                     Deinit();
        static std::shared_ptr<Texture> GetTexture(const std::string& filename);

      private:
        TextureLibrary() : m_MemoryIOSystem(nullptr), m_Textures() {}

        MemoryIOSystem*                                           m_MemoryIOSystem;
        std::unordered_map<std::string, std::shared_ptr<Texture>> m_Textures;
    };
}