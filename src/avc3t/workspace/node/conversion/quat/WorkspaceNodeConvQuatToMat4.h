#pragma once

#include "../../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeConvQuatToMat4 : public WorkspaceNode {
      public:
        WorkspaceNodeConvQuatToMat4();
        WorkspaceNodeConvQuatToMat4(const WorkspaceNodeConvQuatToMat4& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeConvQuatToMat4)

      private:
        glm::mat4 m_OutputValue;
    };
}