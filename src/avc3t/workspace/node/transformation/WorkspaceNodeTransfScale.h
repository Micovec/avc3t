#pragma once

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeTransfScale : public WorkspaceNode {
      public:
        WorkspaceNodeTransfScale();
        WorkspaceNodeTransfScale(const WorkspaceNodeTransfScale& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeTransfScale)

      private:
        glm::mat4 m_Matrix;
    };
}