#pragma once

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeTransfLookAt : public WorkspaceNode {
      public:
        WorkspaceNodeTransfLookAt();
        WorkspaceNodeTransfLookAt(const WorkspaceNodeTransfLookAt& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeTransfLookAt)

      private:
        glm::mat4 m_Matrix;
    };
}
