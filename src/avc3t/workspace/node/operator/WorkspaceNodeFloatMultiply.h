#pragma once

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeFloatMultiply : public WorkspaceNode {
      public:
        WorkspaceNodeFloatMultiply();
        WorkspaceNodeFloatMultiply(const WorkspaceNodeFloatMultiply& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeFloatMultiply)

      private:
        float m_OutputValue;
    };
}