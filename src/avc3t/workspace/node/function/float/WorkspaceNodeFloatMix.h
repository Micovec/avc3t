#pragma once

#include "../../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeFloatMix : public WorkspaceNode {
      public:
        WorkspaceNodeFloatMix();
        WorkspaceNodeFloatMix(const WorkspaceNodeFloatMix& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeFloatMix)

      private:
        float m_OutputValue;
    };
}