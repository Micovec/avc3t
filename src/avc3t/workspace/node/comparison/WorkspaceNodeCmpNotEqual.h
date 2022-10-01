#pragma once

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeCmpNotEqual : public WorkspaceNode {
      public:
        WorkspaceNodeCmpNotEqual();
        WorkspaceNodeCmpNotEqual(const WorkspaceNodeCmpNotEqual& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeCmpNotEqual)

      private:
        bool m_OutputValue;
    };
}