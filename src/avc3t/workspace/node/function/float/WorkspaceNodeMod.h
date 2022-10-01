#pragma once

#include "../../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeMod : public WorkspaceNode {
      public:
        WorkspaceNodeMod();
        WorkspaceNodeMod(const WorkspaceNodeMod& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeMod)

      private:
        float m_OutputValue;
    };
}