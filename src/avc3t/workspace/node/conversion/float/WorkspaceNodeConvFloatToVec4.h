#pragma once

#include "../../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeConvFloatToVec4 : public WorkspaceNode {
      public:
        WorkspaceNodeConvFloatToVec4();
        WorkspaceNodeConvFloatToVec4(const WorkspaceNodeConvFloatToVec4& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeConvFloatToVec4)

      private:
        glm::vec4 m_OutputValue;
    };
}