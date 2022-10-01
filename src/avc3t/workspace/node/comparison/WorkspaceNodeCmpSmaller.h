#pragma once

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeCmpSmaller : public WorkspaceNode {
      public:
        WorkspaceNodeCmpSmaller();
        WorkspaceNodeCmpSmaller(const WorkspaceNodeCmpSmaller& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeCmpSmaller)

      private:
        bool m_OutputValue;
    };
}