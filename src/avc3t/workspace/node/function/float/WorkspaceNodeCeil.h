#pragma once

#include "../../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeCeil : public WorkspaceNode {
      public:
        WorkspaceNodeCeil();
        WorkspaceNodeCeil(const WorkspaceNodeCeil& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeCeil)

      private:
        float m_OutputValue;
    };
}