#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "../render/Texture.h"

namespace AVC3T {
    class TextureLibrary {
      public:
        TextureLibrary(const TextureLibrary& other)                            = delete;
        void                            operator=(const TextureLibrary& other) = delete;

        static TextureLibrary&          GetInstance();

        static void                     FreeTextures();
        static void                     AddTexture(const std::string& filename, const std::shared_ptr<Texture>& texture);
        static std::shared_ptr<Texture> GetTexture(const std::string& filename);

      private:
        TextureLibrary() : m_Textures() {}
        std::unordered_map<std::string, std::shared_ptr<Texture>> m_Textures;
    };
}