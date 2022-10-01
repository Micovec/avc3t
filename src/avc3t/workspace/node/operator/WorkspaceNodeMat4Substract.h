#pragma once

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeMat4Substract : public WorkspaceNode {
      public:
        WorkspaceNodeMat4Substract();
        WorkspaceNodeMat4Substract(const WorkspaceNodeMat4Substract& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeMat4Substract)

      private:
        glm::mat4 m_Matrix;
    };
}