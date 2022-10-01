#include "WorkspaceScalableNode.h"

namespace AVC3T {
    WorkspaceScalableNode::WorkspaceScalableNode(const std::string& title, const std::vector<WorkspaceNodeInput>& inputs, const std::vector<WorkspaceNodeOutput>& outputs,
                                                 const WorkspaceNodeStyle& style, const std::string_view& hint,
                                                 const std::vector<WorkspaceMouseInteractionOption>& additionalOptions) :
        WorkspaceNode(title, inputs, outputs, style, hint, additionalOptions),
        m_Triangle(std::make_shared<WorkspaceScalableTriangle>(this, ImVec2(0, m_TitleSize.y), ImVec2(INFINITY, INFINITY))) {
        m_Children.push_back(m_Triangle);
    }

    WorkspaceScalableNode::WorkspaceScalableNode(const std::string& title, const std::vector<WorkspaceNodeInput>& inputs, const std::vector<WorkspaceNodeOutput>& outputs,
                                                 const WorkspaceNodeStyle& style, const ImVec2& bodySize, const std::string_view& hint,
                                                 const std::vector<WorkspaceMouseInteractionOption>& additionalOptions) :
        WorkspaceNode(title, inputs, outputs, style, bodySize, hint, additionalOptions),
        m_Triangle(std::make_shared<WorkspaceScalableTriangle>(this, ImVec2(m_Style.ContentMargin.x + m_Style.ContentMargin.z, m_TitleSize.y), ImVec2(INFINITY, INFINITY),
                                                               ImVec2(bodySize.x - s_TriangleMargin, bodySize.y - s_TriangleMargin + m_TitleSize.y))) {
        m_Children.push_back(m_Triangle);
    }

    WorkspaceScalableNode::WorkspaceScalableNode(const WorkspaceScalableNode& other) :
        WorkspaceNode(other), m_Triangle(std::make_shared<WorkspaceScalableTriangle>(*other.m_Triangle)) {
        m_Children.push_back(m_Triangle);
    }

    ImVec2 WorkspaceScalableNode::RecalculateContentSize() const {
        ImVec2 contentSize;
        contentSize.x = m_Triangle->GetPosition().x - m_Style.ContentMargin.x - m_Style.ContentMargin.z;
        contentSize.y = m_Triangle->GetPosition().y - m_Style.ContentMargin.y - m_Style.ContentMargin.w - m_TitleSize.y;

        return contentSize;
    }

    void WorkspaceScalableNode::SetSize(const ImVec2& size) {
        ImVec2 trianglePosition(size.x - s_TriangleMargin, size.y - s_TriangleMargin);
        m_Triangle->SetPosition(trianglePosition);
    }
}