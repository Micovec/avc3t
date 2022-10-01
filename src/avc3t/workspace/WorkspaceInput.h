#pragma once

#include <string>

#include <glm/gtc/type_ptr.hpp>

#include "WorkspaceElement.h"
#include "WorkspaceRenderContext.h"

namespace AVC3T {
    class WorkspaceInput : public WorkspaceElement {
      public:
        WorkspaceInput(const std::shared_ptr<WorkspaceOutputPin>& pin, std::size_t id, std::size_t order, float inputWidth, float lineHeight) :
            WorkspaceElement(), m_Pin(pin), m_Id(id), m_Order(order), m_InputWidth(inputWidth), m_LineHeight(lineHeight) {}

        virtual ~WorkspaceInput() {}

        virtual WorkspaceMouseInteractionResult MousePositionUpdate(const WorkspaceMouseInteraction& interaction) override {
            WorkspaceMouseInteractionResult baseResult = WorkspaceElement::MousePositionUpdate(interaction);

            if (baseResult.Type != InteractedElementType_None || interaction.Handled) {
                return baseResult;
            }

            if (IsPositionInsideRectanle(interaction.mousePosition, ImVec2(0, 0), GetSize()))
                return WorkspaceMouseInteractionResult(this, InteractedElementType_Input);

            return WorkspaceMouseInteractionResult();
        }

      protected:
        std::shared_ptr<WorkspaceOutputPin> m_Pin;
        // Order is just an order inside node. When a node has two or more outputs of the same type there's then a collision between ImGui's IDs
        std::size_t m_Id, m_Order;
        float       m_InputWidth, m_LineHeight;
    };

    class WorkspaceInputBool : public WorkspaceInput {
      public:
        WorkspaceInputBool(const std::shared_ptr<WorkspaceOutputPin>& pin, std::size_t id, std::size_t order, float inputWidth, float lineHeight) :
            WorkspaceInput(pin, id, order, inputWidth, lineHeight) {
            m_Size.x = m_Size.y = ImGui::GetFrameHeight();
        }

        virtual void Render(WorkspaceRenderContext& context) override {
            ImVec2 topLeft = m_Position;
            topLeft.x += context.Origin.x;
            topLeft.y += context.Origin.y;

            std::string boolId = "##valueBool" + std::to_string(m_Id) + ";" + std::to_string(m_Order);
            context.DrawList->AddCheckbox(topLeft, boolId, m_Pin->Output.Value.b, m_Pin->Output.LockedIndices & 0x01);
        }
    };

    class WorkspaceInputFloat : public WorkspaceInput {
      public:
        WorkspaceInputFloat(const std::shared_ptr<WorkspaceOutputPin>& pin, std::size_t id, std::size_t order, float inputWidth, float lineHeight) :
            WorkspaceInput(pin, id, order, inputWidth, lineHeight) {
            m_Size.x = inputWidth;
            m_Size.y = lineHeight;
        }

        virtual void Render(WorkspaceRenderContext& context) override {
            ImVec2 topLeft = m_Position;
            topLeft.x += context.Origin.x;
            topLeft.y += context.Origin.y;

            std::string floatId = "##valueFloat" + std::to_string(m_Id) + ";" + std::to_string(m_Order);
            context.DrawList->AddDragFloat(topLeft, floatId, m_Pin->Output.Value.f, m_Pin->Output.LockedIndices & 0x01, m_InputWidth);
        }
    };

    class WorkspaceInputVector3 : public WorkspaceInput {
      public:
        WorkspaceInputVector3(const std::shared_ptr<WorkspaceOutputPin>& pin, std::size_t id, std::size_t order, float inputWidth, float lineHeight) :
            WorkspaceInput(pin, id, order, inputWidth, lineHeight) {
            m_Size.x = inputWidth;
            m_Size.y = lineHeight * 3;
        }

        virtual void Render(WorkspaceRenderContext& context) override {
            ImVec2 topLeft = m_Position;
            ;
            topLeft.x += context.Origin.x;
            topLeft.y += context.Origin.y;

            std::string floatId = "##valueVec3x" + std::to_string(m_Id) + ";" + std::to_string(m_Order);
            context.DrawList->AddDragFloat(ImVec2(topLeft.x, topLeft.y), floatId, &m_Pin->Output.Value.vec3->x, m_Pin->Output.LockedIndices & 0x01, m_InputWidth);

            floatId = "##valueVec3y" + std::to_string(m_Id) + ";" + std::to_string(m_Order);
            context.DrawList->AddDragFloat(ImVec2(topLeft.x, topLeft.y + m_LineHeight), floatId, &m_Pin->Output.Value.vec3->y, m_Pin->Output.LockedIndices & 0x010, m_InputWidth);

            floatId = "##valueVec3z" + std::to_string(m_Id) + ";" + std::to_string(m_Order);
            context.DrawList->AddDragFloat(ImVec2(topLeft.x, topLeft.y + m_LineHeight * 2), floatId, &m_Pin->Output.Value.vec3->z, m_Pin->Output.LockedIndices & 0x0100,
                                           m_InputWidth);
        }
    };

    class WorkspaceInputVector4 : public WorkspaceInput {
      public:
        WorkspaceInputVector4(const std::shared_ptr<WorkspaceOutputPin>& pin, std::size_t id, std::size_t order, float inputWidth, float lineHeight) :
            WorkspaceInput(pin, id, order, inputWidth, lineHeight) {
            m_Size.x = inputWidth;
            m_Size.y = lineHeight * 4;
        }

        virtual void Render(WorkspaceRenderContext& context) override {
            ImVec2 topLeft = m_Position;
            topLeft.x += context.Origin.x;
            topLeft.y += context.Origin.y;

            std::string floatId = "##valueVec4x" + std::to_string(m_Id) + ";" + std::to_string(m_Order);
            context.DrawList->AddDragFloat(ImVec2(topLeft.x, topLeft.y), floatId, &m_Pin->Output.Value.vec4->x, m_Pin->Output.LockedIndices & 0x01, m_InputWidth);

            floatId = "##valueVec4y" + std::to_string(m_Id) + ";" + std::to_string(m_Order);
            context.DrawList->AddDragFloat(ImVec2(topLeft.x, topLeft.y + m_LineHeight), floatId, &m_Pin->Output.Value.vec4->y, m_Pin->Output.LockedIndices & 0x010, m_InputWidth);

            floatId = "##valueVec4z" + std::to_string(m_Id) + ";" + std::to_string(m_Order);
            context.DrawList->AddDragFloat(ImVec2(topLeft.x, topLeft.y + m_LineHeight * 2), floatId, &m_Pin->Output.Value.vec4->z, m_Pin->Output.LockedIndices & 0x0100,
                                           m_InputWidth);

            floatId = "##valueVec4w" + std::to_string(m_Id) + ";" + std::to_string(m_Order);
            context.DrawList->AddDragFloat(ImVec2(topLeft.x, topLeft.y + m_LineHeight * 3), floatId, &m_Pin->Output.Value.vec4->w, m_Pin->Output.LockedIndices & 0x01000,
                                           m_InputWidth);
        }
    };

    class WorkspaceInputMatrix : public WorkspaceInput {
      public:
        WorkspaceInputMatrix(const std::shared_ptr<WorkspaceOutputPin>& pin, std::size_t id, std::size_t order, float inputWidth, float lineHeight) :
            WorkspaceInput(pin, id, order, inputWidth, lineHeight) {
            m_Size.x = m_InputWidth * 4;
            m_Size.y = m_LineHeight * 4;
        }

        virtual void Render(WorkspaceRenderContext& context) override {
            ImVec2 topLeft = m_Position;
            topLeft.x += context.Origin.x;
            topLeft.y += context.Origin.y;

            float* matPtr = glm::value_ptr(*m_Pin->Output.Value.mat4);
            for (int i = 0; i < 4; ++i) {
                for (int k = 0; k < 4; ++k) {
                    std::string mat4Id = "##valueMat4" + std::to_string(i) + ";" + std::to_string(k) + ";" + std::to_string(m_Id) + ";" + ";" + std::to_string(m_Order);
                    context.DrawList->AddDragFloat(ImVec2(topLeft.x + k * m_InputWidth, topLeft.y + i * m_LineHeight), mat4Id, matPtr + i + k * 4,
                                                   m_Pin->Output.LockedIndices & (0x1 << (i + k * 4)), m_InputWidth);
                }
            }
        }
    };

    class WorkspaceInputQuat : public WorkspaceInput {
      public:
        WorkspaceInputQuat(const std::shared_ptr<WorkspaceOutputPin>& pin, std::size_t id, std::size_t order, float inputWidth, float lineHeight) :
            WorkspaceInput(pin, id, order, inputWidth, lineHeight) {
            m_Size.x = inputWidth;
            m_Size.y = lineHeight * 4;
        }

        virtual void Render(WorkspaceRenderContext& context) override {
            ImVec2 topLeft = m_Position;
            topLeft.x += context.Origin.x;
            topLeft.y += context.Origin.y;

            std::string floatId = "##valueQuatx" + std::to_string(m_Id) + ";" + std::to_string(m_Order);
            context.DrawList->AddDragFloat(ImVec2(topLeft.x, topLeft.y), floatId, &m_Pin->Output.Value.quat->x, m_Pin->Output.LockedIndices & 0x01, m_InputWidth);

            floatId = "##valueQuaty" + std::to_string(m_Id) + ";" + std::to_string(m_Order);
            context.DrawList->AddDragFloat(ImVec2(topLeft.x, topLeft.y + m_LineHeight), floatId, &m_Pin->Output.Value.quat->y, m_Pin->Output.LockedIndices & 0x010, m_InputWidth);

            floatId = "##valueQuatz" + std::to_string(m_Id) + ";" + std::to_string(m_Order);
            context.DrawList->AddDragFloat(ImVec2(topLeft.x, topLeft.y + m_LineHeight * 2), floatId, &m_Pin->Output.Value.quat->z, m_Pin->Output.LockedIndices & 0x0100,
                                           m_InputWidth);

            floatId = "##valueQuatw" + std::to_string(m_Id) + ";" + std::to_string(m_Order);
            context.DrawList->AddDragFloat(ImVec2(topLeft.x, topLeft.y + m_LineHeight * 3), floatId, &m_Pin->Output.Value.quat->w, m_Pin->Output.LockedIndices & 0x01000,
                                           m_InputWidth);
        }
    };
} // namespace AVC3T