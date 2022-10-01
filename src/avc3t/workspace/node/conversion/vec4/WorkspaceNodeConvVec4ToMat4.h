#pragma once

#include "../../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeConvVec4ToMat4 : public WorkspaceNode {
      public:
        WorkspaceNodeConvVec4ToMat4();
        WorkspaceNodeConvVec4ToMat4(const WorkspaceNodeConvVec4ToMat4& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeConvVec4ToMat4)

      private:
        glm::mat4 m_OutputValue;
    };
}