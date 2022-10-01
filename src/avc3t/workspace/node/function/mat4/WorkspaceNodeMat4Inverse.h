#pragma once

#include "../../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeMat4Inverse : public WorkspaceNode {
      public:
        WorkspaceNodeMat4Inverse();
        WorkspaceNodeMat4Inverse(const WorkspaceNodeMat4Inverse& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeMat4Inverse)

      private:
        glm::mat4 m_OutputValue;
    };
}