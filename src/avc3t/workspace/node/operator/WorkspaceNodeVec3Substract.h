#pragma once

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeVec3Substract : public WorkspaceNode {
      public:
        WorkspaceNodeVec3Substract();
        WorkspaceNodeVec3Substract(const WorkspaceNodeVec3Substract& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeVec3Substract)

      private:
        glm::vec3 m_OutputValue;
    };
}