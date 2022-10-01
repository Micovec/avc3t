#pragma once

#include <memory>
#include <string>

#include <glm/glm.hpp>

#include "../render/Texture.h"

namespace AVC3T {
    struct Material {
        Material(const glm::vec3& ambient, const glm::vec3& diffuse, const std::shared_ptr<Texture>& texture) : AmbientColor(ambient), DiffuseColor(diffuse), texture(texture) {}

        // We don't care much about other colors
        const glm::vec3                AmbientColor;
        const glm::vec3                DiffuseColor;

        const std::shared_ptr<Texture> texture;
    };
} // namespace AVC3T