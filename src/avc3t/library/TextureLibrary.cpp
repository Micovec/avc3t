#include "TextureLibrary.h"

namespace AVC3T {
    TextureLibrary& TextureLibrary::GetInstance() {
        static TextureLibrary library;
        return library;
    }

    void TextureLibrary::AddTexture(const std::string& filename, const std::shared_ptr<Texture>& texture) {
        GetInstance().m_Textures.emplace(filename, texture);
    }

    std::shared_ptr<Texture> TextureLibrary::GetTexture(const std::string& filename) {
        TextureLibrary& library = GetInstance();
        auto            texture = library.m_Textures.find(filename);
        if (texture != library.m_Textures.end())
            return texture->second;

        return nullptr;
    }

    void TextureLibrary::FreeTextures() {
        GetInstance().m_Textures.clear();
    }
}