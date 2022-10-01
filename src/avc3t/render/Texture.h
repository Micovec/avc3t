#pragma once

#include "../utils/Macros.h"

namespace AVC3T {
    class Texture {
      public:
        Texture(int width, int height, int componentCount, const unsigned char* data);
        Texture(const Texture& other) = delete;

        ~Texture();

        void operator=(const Texture& other) = delete;

        void Bind() const;
        void Unbind() const;

        bool ContainsTransparent() const {
            return m_ComponentCount == 4;
        }
        int GetWidth() const {
            return m_Width;
        }
        int GetHeight() const {
            return m_Height;
        }
        int GetComponentCount() const {
            return m_ComponentCount;
        }

      public:
        static GLenum GetFormatFromComponentCount(int componentCount) {
            switch (componentCount) {
                case 1: return GL_RED;
                case 3: return GL_RGB;
                case 4: return GL_RGBA;
                default: return 0;
            }
        }

      private:
        unsigned int m_TextureID;
        int          m_Width, m_Height, m_ComponentCount;
    };
}