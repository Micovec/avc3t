#pragma once

#include "../../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeConvFloatToMat4 : public WorkspaceNode {
      public:
        WorkspaceNodeConvFloatToMat4();
        WorkspaceNodeConvFloatToMat4(const WorkspaceNodeConvFloatToMat4& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeConvFloatToMat4)

      private:
        glm::mat4 m_OutputValue;
    };
}