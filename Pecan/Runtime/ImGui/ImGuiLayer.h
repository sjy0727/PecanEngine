#pragma once

#include "Runtime/Core/Layer.h"
#include "Runtime/Events/ApplicationEvent.h"
#include "Runtime/Events/KeyEvent.h"
#include "Runtime/Events/MouseEvent.h"

namespace Pecan
{
    class ImGuiLayer : public Layer
    {
    private:
        float m_Time        = 0.0f;
        bool  m_BlockEvents = true;

    public:
        ImGuiLayer();
        ~ImGuiLayer() override;

        void OnAttach() override;
        void OnDetach() override;
        void OnEvent(SDL_Event& e) override;

        void SetDarkThemeColors();

        void Begin();
        void End();

        void BlockEvents(bool block) { m_BlockEvents = block; }
        // void OnEvent(Event& event) override;
    };
} // namespace Pecan