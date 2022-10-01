#pragma once

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeTransfRotationVector : public WorkspaceNode {
      public:
        WorkspaceNodeTransfRotationVector();
        WorkspaceNodeTransfRotationVector(const WorkspaceNodeTransfRotationVector& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeTransfRotationVector)

      private:
        glm::mat4 m_Matrix;
    };
}
