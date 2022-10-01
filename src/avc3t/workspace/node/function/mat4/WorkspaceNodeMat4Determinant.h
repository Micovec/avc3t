#pragma once

#include "../../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeMat4Determinant : public WorkspaceNode {
      public:
        WorkspaceNodeMat4Determinant();
        WorkspaceNodeMat4Determinant(const WorkspaceNodeMat4Determinant& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeMat4Determinant)

      private:
        float m_OutputValue;
    };
}