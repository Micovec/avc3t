#pragma once

#include "../../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeConvVec3Vec3ToQuat : public WorkspaceNode {
      public:
        WorkspaceNodeConvVec3Vec3ToQuat();
        WorkspaceNodeConvVec3Vec3ToQuat(const WorkspaceNodeConvVec3Vec3ToQuat& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeConvVec3Vec3ToQuat)

      private:
        glm::quat m_OutputValue;
    };
}