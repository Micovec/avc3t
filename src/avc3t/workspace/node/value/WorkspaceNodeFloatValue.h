#pragma once

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeFloatValue : public WorkspaceNode {
      public:
        WorkspaceNodeFloatValue();
        WorkspaceNodeFloatValue(const WorkspaceNodeFloatValue& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeFloatValue)

      private:
        float m_Value;
    };
}