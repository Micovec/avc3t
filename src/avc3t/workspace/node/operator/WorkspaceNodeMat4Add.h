#pragma once

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeMat4Add : public WorkspaceNode {
      public:
        WorkspaceNodeMat4Add();
        WorkspaceNodeMat4Add(const WorkspaceNodeMat4Add& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeMat4Add)

      private:
        glm::mat4 m_Matrix;
    };
}