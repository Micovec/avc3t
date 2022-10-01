#pragma once

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeFloatDivide : public WorkspaceNode {
      public:
        WorkspaceNodeFloatDivide();
        WorkspaceNodeFloatDivide(const WorkspaceNodeFloatDivide& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeFloatDivide)

      private:
        float m_OutputValue;
    };
}