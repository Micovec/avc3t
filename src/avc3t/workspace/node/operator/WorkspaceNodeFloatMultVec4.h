#pragma once

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeFloatMultVec4 : public WorkspaceNode {
      public:
        WorkspaceNodeFloatMultVec4();
        WorkspaceNodeFloatMultVec4(const WorkspaceNodeFloatMultVec4& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeFloatMultVec4)

      private:
        glm::vec4 m_OutputValue;
    };
}