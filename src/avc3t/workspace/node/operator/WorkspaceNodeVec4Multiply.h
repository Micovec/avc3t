#pragma once

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeVec4Multiply : public WorkspaceNode {
      public:
        WorkspaceNodeVec4Multiply();
        WorkspaceNodeVec4Multiply(const WorkspaceNodeVec4Multiply& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeVec4Multiply)

      private:
        glm::vec4 m_OutputValue;
    };
}