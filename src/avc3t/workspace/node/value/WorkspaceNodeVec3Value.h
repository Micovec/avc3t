#pragma once

#include <glm/glm.hpp>

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeVec3Value : public WorkspaceNode {
      public:
        WorkspaceNodeVec3Value();
        WorkspaceNodeVec3Value(const WorkspaceNodeVec3Value& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeVec3Value)

      private:
        glm::vec3 m_Vec3;
    };
}