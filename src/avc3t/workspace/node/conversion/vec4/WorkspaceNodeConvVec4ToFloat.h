#pragma once

#include "../../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeConvVec4ToFloat : public WorkspaceNode {
      public:
        WorkspaceNodeConvVec4ToFloat();
        WorkspaceNodeConvVec4ToFloat(const WorkspaceNodeConvVec4ToFloat& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeConvVec4ToFloat)

      private:
        float m_OutputValue0;
        float m_OutputValue1;
        float m_OutputValue2;
        float m_OutputValue3;
    };
}