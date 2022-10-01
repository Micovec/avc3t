#pragma once

#include <glm/glm.hpp>

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeFloatMultMat4 : public WorkspaceNode {
      public:
        WorkspaceNodeFloatMultMat4();
        WorkspaceNodeFloatMultMat4(const WorkspaceNodeFloatMultMat4& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeFloatMultMat4)

      private:
        glm::mat4 m_OutputValue;
    };
}