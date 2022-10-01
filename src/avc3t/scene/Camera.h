#pragma once

namespace AVC3T {
    class Camera {
      public:
        Camera() : m_Projection(1.0f), m_View(1.0f) {}

        glm::mat4 GetViewMatrix() {
            return m_View;
        }
        glm::mat4 GetPVMatrix() {
            return m_Projection * m_View;
        }
        glm::mat4 GetProjectionMatrix() {
            return m_Projection;
        }

      protected:
        glm::mat4 m_Projection, m_View;
    };
}