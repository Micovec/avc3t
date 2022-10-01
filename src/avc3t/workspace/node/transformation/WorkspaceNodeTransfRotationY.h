#pragma once

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeTransfRotationY : public WorkspaceNode {
      public:
        WorkspaceNodeTransfRotationY();
        WorkspaceNodeTransfRotationY(const WorkspaceNodeTransfRotationY& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeTransfRotationY)

      private:
        glm::mat4 m_Matrix;
    };
}