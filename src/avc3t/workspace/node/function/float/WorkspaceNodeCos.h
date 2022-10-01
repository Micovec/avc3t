#pragma once

#include "../../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeCos : public WorkspaceNode {
      public:
        WorkspaceNodeCos();
        WorkspaceNodeCos(const WorkspaceNodeCos& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeCos)

      private:
        float m_OutputValue;
    };
}