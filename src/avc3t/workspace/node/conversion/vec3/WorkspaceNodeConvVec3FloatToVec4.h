#pragma once

#include "../../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeConvVec3FloatToVec4 : public WorkspaceNode {
      public:
        WorkspaceNodeConvVec3FloatToVec4();
        WorkspaceNodeConvVec3FloatToVec4(const WorkspaceNodeConvVec3FloatToVec4& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeConvVec3FloatToVec4)

      private:
        glm::vec4 m_OutputValue;
    };
}