#pragma once

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeFloatPower : public WorkspaceNode {
      public:
        WorkspaceNodeFloatPower();
        WorkspaceNodeFloatPower(const WorkspaceNodeFloatPower& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeFloatPower)

      private:
        float m_OutputValue;
    };
}