#pragma once

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeFloatAdd : public WorkspaceNode {
      public:
        WorkspaceNodeFloatAdd();
        WorkspaceNodeFloatAdd(const WorkspaceNodeFloatAdd& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeFloatAdd)

      private:
        float m_OutputValue;
    };
}