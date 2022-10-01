#pragma once

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeFloatSubstract : public WorkspaceNode {
      public:
        WorkspaceNodeFloatSubstract();
        WorkspaceNodeFloatSubstract(const WorkspaceNodeFloatSubstract& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeFloatSubstract)

      private:
        float m_OutputValue;
    };
}