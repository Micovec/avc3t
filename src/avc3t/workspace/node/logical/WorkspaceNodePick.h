#pragma once

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodePick : public WorkspaceNode {
      public:
        WorkspaceNodePick();
        WorkspaceNodePick(const WorkspaceNodePick& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodePick)

      private:
        bool m_OutputValueBool;

      private:
        constexpr static WorkspaceIOType s_AllIOTypes =
            WorkspaceIOType_Bool | WorkspaceIOType_Float | WorkspaceIOType_Vec3 | WorkspaceIOType_Vec4 | WorkspaceIOType_Mat4 | WorkspaceIOType_Quat;
    };
}