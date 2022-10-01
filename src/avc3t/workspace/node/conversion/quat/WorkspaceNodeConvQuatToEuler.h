#pragma once

#include "../../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeConvQuatToEuler : public WorkspaceNode {
      public:
        WorkspaceNodeConvQuatToEuler();
        WorkspaceNodeConvQuatToEuler(const WorkspaceNodeConvQuatToEuler& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeConvQuatToEuler)

      private:
        float m_OutputValue0;
        float m_OutputValue1;
        float m_OutputValue2;
    };
}