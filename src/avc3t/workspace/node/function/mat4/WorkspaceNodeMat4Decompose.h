#pragma once

#include "../../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeMat4Decompose : public WorkspaceNode {
      public:
        WorkspaceNodeMat4Decompose();
        WorkspaceNodeMat4Decompose(const WorkspaceNodeMat4Decompose& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeMat4Decompose)

      private:
        glm::vec3 m_Translation;
        glm::vec3 m_Scale;
        glm::quat m_Rotation;
        glm::vec3 m_Skew;
        glm::vec4 m_Perspective;
    };
}