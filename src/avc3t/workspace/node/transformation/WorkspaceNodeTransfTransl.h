#pragma once

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeTransfTransl : public WorkspaceNode {
      public:
        WorkspaceNodeTransfTransl();
        WorkspaceNodeTransfTransl(const WorkspaceNodeTransfTransl& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeTransfTransl);

      private:
        glm::mat4 m_Matrix;
    };
}