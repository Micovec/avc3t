#pragma once

#include "../../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeVec3Length : public WorkspaceNode {
      public:
        WorkspaceNodeVec3Length();
        WorkspaceNodeVec3Length(const WorkspaceNodeVec3Length& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeVec3Length)

      private:
        float m_OutputValue;
    };
}