#include "Texture.h"

namespace AVC3T {
    Texture::Texture(int width, int height, int componentCount, const unsigned char* data) : m_Width(width), m_Height(height), m_ComponentCount(componentCount) {
        GLCall(glGenTextures(1, &m_TextureID));

        GLenum format = GetFormatFromComponentCount(m_ComponentCount);

        Bind();
        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data));
        GLCall(glGenerateMipmap(GL_TEXTURE_2D));

        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    }

    Texture::~Texture() {
        GLCall(glDeleteTextures(1, &m_TextureID));
    }

    void Texture::Bind() const {
        GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID));
    }

    void Texture::Unbind() const {
        GLCall(glBindTexture(GL_TEXTURE_2D, 0));
    }
}