#pragma once

#include "../../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeMat4Transpose : public WorkspaceNode {
      public:
        WorkspaceNodeMat4Transpose();
        WorkspaceNodeMat4Transpose(const WorkspaceNodeMat4Transpose& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeMat4Transpose)

      private:
        glm::mat4 m_OutputValue;
    };
}