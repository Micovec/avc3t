#pragma once

#include <glm/ext.hpp>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL // For matrix decomposition
#include <glm/gtx/matrix_decompose.hpp>

#include <imgui.h>

#include "Camera.h"

namespace AVC3T {
    class EditorCamera : public Camera {
      public:
        EditorCamera(float fov, float near, float far) :
            m_Rotation(s_RotationX, 0), m_LookAt(0, 0, 0), m_Fov(fov), m_Near(near), m_Far(far), m_Aspect(1), m_OriginDistance(s_OriginDistance), m_LastMousePos(0, 0),
            m_MouseFlags(0), m_StartedMoving(false) {
            m_View = m_Projection = glm::mat4(0.0f);

            CalculateProjectionMatrix();
            CalculateViewMatrix();
        }

        void Update() {
            ImVec2 currentMousePos = ImGui::GetMousePos();

            m_MouseFlags |= ImGui::IsMouseClicked(ImGuiMouseButton_Right) ? ImGuiMouseButton_Right : 0;
            m_MouseFlags |= ImGui::IsMouseClicked(ImGuiMouseButton_Middle) ? ImGuiMouseButton_Middle : 0;

            if (ImGui::IsMouseClicked(ImGuiMouseButton_Right) || ImGui::IsMouseClicked(ImGuiMouseButton_Middle))
                m_LastMousePos = currentMousePos;

            ImVec2 mouseDelta((currentMousePos.x - m_LastMousePos.x) * s_MouseSensitivity, (currentMousePos.y - m_LastMousePos.y) * s_MouseSensitivity);
            float  mouseDeltaLength = glm::abs(currentMousePos.x - m_LastMousePos.x) + glm::abs(currentMousePos.y - m_LastMousePos.y);

            if ((m_MouseFlags && mouseDeltaLength > 0) || m_StartedMoving)
                ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);
            if (ImGui::IsMouseReleased(m_MouseFlags & ImGuiMouseButton_Right) || ImGui::IsMouseReleased(m_MouseFlags & ImGuiMouseButton_Middle)) {
                ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
                m_MouseFlags    = 0;
                m_StartedMoving = false;
            }

            m_OriginDistance += ImGui::GetIO().MouseWheel;

            m_StartedMoving = mouseDeltaLength != 0 && m_MouseFlags;

            if (ImGui::IsMouseDown(ImGuiMouseButton_Right)) {
                glm::vec3 diff(mouseDelta.x, -mouseDelta.y, 0);

                diff = diff * glm::quat(glm::vec3(m_Rotation.x, 0, 0)) * glm::quat(glm::vec3(0, m_Rotation.y, 0));

                diff *= -m_OriginDistance * s_MouseSensitivity * 40;

                m_LookAt.x += diff.x;
                m_LookAt.y += diff.y;
                m_LookAt.z += diff.z;
            } else if (ImGui::IsMouseDown(ImGuiMouseButton_Middle)) {
                m_Rotation.x += mouseDelta.y;
                m_Rotation.y += mouseDelta.x;
            }

            CalculateViewMatrix();

            m_LastMousePos = currentMousePos;
        }

        void SetAspect(float aspect) {
            m_Aspect = aspect;
            CalculateProjectionMatrix();
        }

        void SetOriginDistance(float distance) {
            m_OriginDistance = distance;
            CalculateViewMatrix();
        }

        void SetLookAt(const glm::vec3& lookAt) {
            m_LookAt = lookAt;
            CalculateViewMatrix();
        }

        void Reset() {
            m_LookAt.x = m_LookAt.y = m_LookAt.z = 0;
            m_Rotation.x                         = s_RotationX;
            m_Rotation.y                         = 0;
            m_OriginDistance                     = s_OriginDistance;
            CalculateViewMatrix();
        }

      private:
        void CalculateProjectionMatrix() {
            m_Projection = glm::perspective(m_Fov, m_Aspect, m_Near, m_Far);
        }

        void CalculateViewMatrix() {
            m_View = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, m_OriginDistance));
            m_View = glm::rotate(m_View, m_Rotation.x, glm::vec3(1, 0, 0));
            m_View = glm::rotate(m_View, m_Rotation.y, glm::vec3(0, 1, 0));
            m_View = glm::translate(m_View, m_LookAt);
        }

      private:
        static constexpr float s_MouseSensitivity = 0.0075f;
        static constexpr float s_OriginDistance   = -10.f;
        static constexpr float s_RotationX        = 0.5f;

        glm::vec2              m_Rotation; // Local rotation, only x and y

        glm::vec3              m_LookAt; // Point which we rotate around
        const float            m_Fov, m_Near, m_Far;
        float                  m_Aspect, m_OriginDistance;
        ImVec2                 m_LastMousePos;
        ImGuiMouseButton       m_MouseFlags;
        bool                   m_StartedMoving;
    };
}