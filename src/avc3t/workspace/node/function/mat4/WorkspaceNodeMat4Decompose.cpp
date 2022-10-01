#include "WorkspaceNodeMat4Decompose.h"

#define GLM_ENABLE_EXPERIMENTAL // For matrix decomposition
#include <glm/gtx/matrix_decompose.hpp>

namespace AVC3T {
    WorkspaceNodeMat4Decompose::WorkspaceNodeMat4Decompose() :
        WorkspaceNode("Decompose Mat4", {WorkspaceNodeInput(WorkspaceIOType_Mat4)},
                      {WorkspaceNodeOutput(WorkspaceIOType_Vec3, {&m_Translation}, -1, "translation"), WorkspaceNodeOutput(WorkspaceIOType_Vec3, {&m_Scale}, -1, "scale"),
                       WorkspaceNodeOutput(WorkspaceIOType_Quat, {&m_Rotation}, -1, "rotation"), WorkspaceNodeOutput(WorkspaceIOType_Vec3, {&m_Skew}, -1, "skew"),
                       WorkspaceNodeOutput(WorkspaceIOType_Vec3, {&m_Perspective}, -1, "perspective")},
                      {IM_COL32(190, 35, 52, 255)}),
        m_Translation(0), m_Scale(0), m_Rotation(0, 0, 0, 0), m_Skew(0), m_Perspective(0) {}

    WorkspaceNodeMat4Decompose::WorkspaceNodeMat4Decompose(const WorkspaceNodeMat4Decompose& other) :
        WorkspaceNode(other.m_Title, {WorkspaceNodeInput(WorkspaceIOType_Mat4)},
                      {WorkspaceNodeOutput(WorkspaceIOType_Vec3, {&m_Translation}, -1, "translation"), WorkspaceNodeOutput(WorkspaceIOType_Vec3, {&m_Scale}, -1, "scale"),
                       WorkspaceNodeOutput(WorkspaceIOType_Quat, {&m_Rotation}, -1, "rotation"), WorkspaceNodeOutput(WorkspaceIOType_Vec3, {&m_Skew}, -1, "skew"),
                       WorkspaceNodeOutput(WorkspaceIOType_Vec3, {&m_Perspective}, -1, "perspective")},
                      other.m_Style, other.m_BodySize, other.m_Hint->GetHintText()),
        m_Translation(0), m_Scale(0), m_Rotation(0, 0, 0, 0), m_Skew(0), m_Perspective(0) {}

    void WorkspaceNodeMat4Decompose::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin> input0 = m_InputPins[0];

        if (input0->Link == nullptr)
            return;

        glm::decompose(*input0->Link->OutputPin.Output.Value.mat4, m_Scale, m_Rotation, m_Translation, m_Skew, m_Perspective);
    }
}