#pragma once

#include <glm/glm.hpp>

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeFloatMultQuat : public WorkspaceNode {
      public:
        WorkspaceNodeFloatMultQuat();
        WorkspaceNodeFloatMultQuat(const WorkspaceNodeFloatMultQuat& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeFloatMultQuat)

      private:
        glm::quat m_OutputValue;
    };
}