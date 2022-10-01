#pragma once

#include "../../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeVec4Normalize : public WorkspaceNode {
      public:
        WorkspaceNodeVec4Normalize();
        WorkspaceNodeVec4Normalize(const WorkspaceNodeVec4Normalize& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeVec4Normalize)

      private:
        glm::vec4 m_OutputValue;
    };
}