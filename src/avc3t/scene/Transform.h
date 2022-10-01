#pragma once

#include <glm/glm.hpp>
#include <glm/ext/quaternion_float.hpp>

namespace AVC3T {
    struct Transform {
        Transform() : Matrix(1.0f) {}

        glm::mat4 Matrix;
    };
}