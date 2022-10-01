#pragma once

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeTransfRotationX : public WorkspaceNode {
      public:
        WorkspaceNodeTransfRotationX();
        WorkspaceNodeTransfRotationX(const WorkspaceNodeTransfRotationX& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeTransfRotationX)

      private:
        glm::mat4 m_Matrix;
    };
}