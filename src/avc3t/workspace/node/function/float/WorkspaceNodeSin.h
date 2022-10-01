#pragma once

#include "../../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeSin : public WorkspaceNode {
      public:
        WorkspaceNodeSin();
        WorkspaceNodeSin(const WorkspaceNodeSin& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeSin)

      private:
        float m_OutputValue;
    };
}