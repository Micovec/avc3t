#pragma once

#include "glm/glm.hpp"
#include "Camera.h"

namespace AVC3T {
    class StaticCamera : public Camera {
      public:
        void SetViewMatrix(const glm::mat4& matrix) {
            m_View = matrix;
        }
        void SetProjectionMatrix(const glm::mat4& matrix) {
            m_Projection = matrix;
        }
    };
}