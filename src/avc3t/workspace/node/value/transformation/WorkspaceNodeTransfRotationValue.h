#pragma once

#include "../../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeTransfRotationValue : public WorkspaceNode {
      public:
        WorkspaceNodeTransfRotationValue();
        WorkspaceNodeTransfRotationValue(const WorkspaceNodeTransfRotationValue& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeTransfRotationValue)

      private:
        glm::mat4 m_Matrix;
    };
}