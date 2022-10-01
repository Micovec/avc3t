#pragma once

#include "../../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeTransfScaleValue : public WorkspaceNode {
      public:
        WorkspaceNodeTransfScaleValue();
        WorkspaceNodeTransfScaleValue(const WorkspaceNodeTransfScaleValue& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeTransfScaleValue)

      private:
        glm::mat4 m_Matrix;
    };
}