#pragma once

#include "../../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeConvVec3ToFloat : public WorkspaceNode {
      public:
        WorkspaceNodeConvVec3ToFloat();
        WorkspaceNodeConvVec3ToFloat(const WorkspaceNodeConvVec3ToFloat& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeConvVec3ToFloat)

      private:
        float m_OutputValue0;
        float m_OutputValue1;
        float m_OutputValue2;
    };
}