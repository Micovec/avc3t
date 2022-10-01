#pragma once

#include "../../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeConvVec4ToVec3Float : public WorkspaceNode {
      public:
        WorkspaceNodeConvVec4ToVec3Float();
        WorkspaceNodeConvVec4ToVec3Float(const WorkspaceNodeConvVec4ToVec3Float& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeConvVec4ToVec3Float)

      private:
        glm::vec3 m_OutputValue0;
        float     m_OutputValue1;
    };
}