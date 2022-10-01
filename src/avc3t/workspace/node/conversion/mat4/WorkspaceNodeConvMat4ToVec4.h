#pragma once

#include "../../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeConvMat4ToVec4 : public WorkspaceNode {
      public:
        WorkspaceNodeConvMat4ToVec4();
        WorkspaceNodeConvMat4ToVec4(const WorkspaceNodeConvMat4ToVec4& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeConvMat4ToVec4)

      private:
        glm::vec4 m_OutputValue0;
        glm::vec4 m_OutputValue1;
        glm::vec4 m_OutputValue2;
        glm::vec4 m_OutputValue3;
    };
}