#pragma once

#include <glm/glm.hpp>

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeMat4MultVec4 : public WorkspaceNode {
      public:
        WorkspaceNodeMat4MultVec4();
        WorkspaceNodeMat4MultVec4(const WorkspaceNodeMat4MultVec4& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeMat4MultVec4)

      private:
        glm::vec4 m_OutputValue;
    };
}