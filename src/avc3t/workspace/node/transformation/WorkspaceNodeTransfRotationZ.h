#pragma once

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeTransfRotationZ : public WorkspaceNode {
      public:
        WorkspaceNodeTransfRotationZ();
        WorkspaceNodeTransfRotationZ(const WorkspaceNodeTransfRotationZ& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeTransfRotationZ)

      private:
        glm::mat4 m_Matrix;
    };
}