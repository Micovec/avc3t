#include "TextureLibrary.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace AVC3T {
    TextureLibrary& TextureLibrary::GetInstance() {
        static TextureLibrary library;
        return library;
    }

    void TextureLibrary::Init(MemoryIOSystem& memoryIOSystem) {
        GetInstance().m_MemoryIOSystem = &memoryIOSystem;
    }

    // void TextureLibrary::AddTexture(const std::string& filename, const std::shared_ptr<Texture>& texture) {
    //     GetInstance().m_Textures.emplace(filename, texture);
    // }

    std::shared_ptr<Texture> TextureLibrary::GetTexture(const std::string& filename) {
        TextureLibrary& instance  = GetInstance();
        auto            textureIt = instance.m_Textures.find(filename);

        // If the texture is already in loaded textures, return it.
        if (textureIt != instance.m_Textures.end())
            return textureIt->second;

        // Opengl has 0,0 at the bottom left corner whereas png at top left -> flip it
        // horizontally
        stbi_set_flip_vertically_on_load(true);

        const MemoryFile&        file = instance.m_MemoryIOSystem->OpenFile(filename);

        int                      width, height, nrComponents;
        unsigned char*           data = stbi_load_from_memory(file.GetRaw(), file.GetLength(), &width, &height, &nrComponents, 0);

        std::shared_ptr<Texture> texture = std::make_shared<Texture>(width, height, nrComponents, data);

        // Cleanup
        stbi_image_free(data);

        instance.m_Textures.insert({filename, texture});

        return texture;
    }

    void TextureLibrary::Deinit() {
        TextureLibrary& instance = GetInstance();

        instance.m_Textures.clear();
        instance.m_MemoryIOSystem = nullptr;
    }
}