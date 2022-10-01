#pragma once

#include "../../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeConvFloatToVec3 : public WorkspaceNode {
      public:
        WorkspaceNodeConvFloatToVec3();
        WorkspaceNodeConvFloatToVec3(const WorkspaceNodeConvFloatToVec3& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeConvFloatToVec3)

      private:
        glm::vec3 m_OutputValue;
    };
}