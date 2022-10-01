#pragma once

#include "../../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeAbs : public WorkspaceNode {
      public:
        WorkspaceNodeAbs();
        WorkspaceNodeAbs(const WorkspaceNodeAbs& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeAbs)

      private:
        float m_OutputValue;
    };
}