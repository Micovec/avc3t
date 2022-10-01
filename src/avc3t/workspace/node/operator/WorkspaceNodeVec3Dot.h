#pragma once

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeVec3Dot : public WorkspaceNode {
      public:
        WorkspaceNodeVec3Dot();
        WorkspaceNodeVec3Dot(const WorkspaceNodeVec3Dot& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeVec3Dot)

      private:
        float m_OutputValue;
    };
}