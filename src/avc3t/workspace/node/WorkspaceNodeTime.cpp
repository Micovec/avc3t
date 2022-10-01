#include "WorkspaceNodeTime.h"

namespace AVC3T {
    WorkspaceNodeTime::WorkspaceNodeTime() :
        WorkspaceNode("Time", {},
                      {WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_Delta}, -1, "Delta"), WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_SystemTime}, -1, "System time")},
                      {IM_COL32(190, 35, 52, 255)}),
        m_Delta(0), m_SystemTime(0) {}

    WorkspaceNodeTime::WorkspaceNodeTime(const WorkspaceNodeTime& other) :
        WorkspaceNode(other.m_Title, {},
                      {WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_Delta}, -1, "Delta"), WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_SystemTime}, -1, "System time")},
                      other.m_Style, other.m_BodySize, other.m_Hint->GetHintText()),
        m_Delta(other.m_Delta), m_SystemTime(other.m_SystemTime) {}

    void WorkspaceNodeTime::Evaluate(double ts) {
        // MAGIC: 10e302. Because of conversion from double to float we lose some precision and ts might not be equal to m_SystemTime from last call when the time is paused
        // We need to adjust accordingly by multiplying with a *random* number
        if (std::abs(ts - m_SystemTime) <= std::numeric_limits<double>::min() * 10e302)
            return;

        m_Delta      = static_cast<float>(std::max(ts - m_SystemTime, 0.));
        m_SystemTime = static_cast<float>(ts);
    }
}