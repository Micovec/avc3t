#pragma once

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeCmpEqual : public WorkspaceNode {
      public:
        WorkspaceNodeCmpEqual();
        WorkspaceNodeCmpEqual(const WorkspaceNodeCmpEqual& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeCmpEqual)

      private:
        bool m_OutputValue;
    };
}