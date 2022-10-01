#pragma once

#include <glm/glm.hpp>

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeVec4Value : public WorkspaceNode {
      public:
        WorkspaceNodeVec4Value();
        WorkspaceNodeVec4Value(const WorkspaceNodeVec4Value& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeVec4Value)

      private:
        glm::vec4 m_Vec4;
    };
}