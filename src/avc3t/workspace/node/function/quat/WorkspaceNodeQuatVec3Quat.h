#pragma once

#include <glm/glm.hpp>

#include "../../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeQuatVec3Quat : public WorkspaceNode {
      public:
        WorkspaceNodeQuatVec3Quat();
        WorkspaceNodeQuatVec3Quat(const WorkspaceNodeQuatVec3Quat& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeQuatVec3Quat)

      private:
        glm::vec3 m_OutputValue;
    };
}