#pragma once

#include "../../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeAsin : public WorkspaceNode {
      public:
        WorkspaceNodeAsin();
        WorkspaceNodeAsin(const WorkspaceNodeAsin& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeAsin)

      private:
        float m_OutputValue;
    };
}