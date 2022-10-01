#pragma once

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeFloatMultVec3 : public WorkspaceNode {
      public:
        WorkspaceNodeFloatMultVec3();
        WorkspaceNodeFloatMultVec3(const WorkspaceNodeFloatMultVec3& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeFloatMultVec3)

      private:
        glm::vec3 m_OutputValue;
    };
}