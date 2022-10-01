#pragma once

#include "../../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeConvQuatToFloat : public WorkspaceNode {
      public:
        WorkspaceNodeConvQuatToFloat();
        WorkspaceNodeConvQuatToFloat(const WorkspaceNodeConvQuatToFloat& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeConvQuatToFloat)

      private:
        float m_OutputValue0;
        float m_OutputValue1;
        float m_OutputValue2;
        float m_OutputValue3;
    };
}