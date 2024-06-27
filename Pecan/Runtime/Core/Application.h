#pragma once

#include "Runtime/Core/Base.h"

#include "Runtime/Core/LayerStack.h"
#include "Runtime/Core/Timestep.h"
#include "Runtime/Core/Window.h"

#include "Runtime/Events/ApplicationEvent.h"
#include "Runtime/Events/Event.h"

#include "Runtime/ImGui/ImGuiLayer.h"
#include "SDL.h"

int main(int argc, char* argv[]);

namespace Pecan
{
    class Application
    {
    private:
        static SDL_Renderer* m_Renderer;
        SDL_Event            m_Event;

    private:
        Scope<Window> m_Window;
        ImGuiLayer*   m_ImGuiLayer;
        bool          m_Running   = true;
        bool          m_Minimized = false;
        LayerStack    m_LayerStack;
        float         m_LastFrameTime = 0.0f;

    private:
        void Run();
        //        bool OnWindowClose(WindowCloseEvent& e);
        //        bool OnWindowResize(WindowResizeEvent& e);

    private:
        friend int ::main(int argc, char* argv[]);
        static Application* s_Instance;

    public:
        Application(const std::string& name = "Pecan");
        virtual ~Application();

        //        void OnEvent(Event& e);
        void OnEvent(SDL_Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        inline static Application&  Get() { return *s_Instance; }
        inline Window&              GetWindow() { return *m_Window; }
        inline static SDL_Renderer* GetRenderer() { return m_Renderer; }
        inline static void          SetRenderer(SDL_Renderer* renderer) { m_Renderer = renderer; }

        inline void        Close() { m_Running = false; };
        inline ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }
    };

    // 在客户端(Sandbox)中定义
    Application* CreateApplication();

} // namespace Pecan
