#pragma once

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeCmpSmallerEqual : public WorkspaceNode {
      public:
        WorkspaceNodeCmpSmallerEqual();
        WorkspaceNodeCmpSmallerEqual(const WorkspaceNodeCmpSmallerEqual& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeCmpSmallerEqual)

      private:
        bool m_OutputValue;
    };
}