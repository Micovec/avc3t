#pragma once

#include "../../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeAcos : public WorkspaceNode {
      public:
        WorkspaceNodeAcos();
        WorkspaceNodeAcos(const WorkspaceNodeAcos& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeAcos)

      private:
        float m_OutputValue;
    };
}