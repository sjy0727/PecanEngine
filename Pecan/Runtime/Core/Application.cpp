#include "pcpch.h"

#include "Runtime/Core/Application.h"
#include "Runtime/Core/Assert.h"
#include "Runtime/Core/Log.h"

#include "Runtime/Renderer/RenderCommand.h"
#include "Runtime/Renderer/Renderer.h"

#include "SDL.h"
#include "imgui_impl_sdl2.h"

namespace Pecan
{

    Application*  Application::s_Instance = nullptr;
    SDL_Renderer* Application::m_Renderer = nullptr;

    Application::Application(const std::string& name)
    {
        PC_PROFILE_FUNCTION();

        PC_CORE_ASSERT(s_Instance == nullptr, "Application already exists!");
        s_Instance = this;

        m_Window = Window::Create(WindowProps(name));
        //        m_Window->SetEventCallback(PC_BIND_EVENT_FN(OnEvent));

        // 初始化renderer
        Renderer::Init(
            (SDL_Window*)m_Window->GetNativeWindow(), -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

        // application是单例的所以不用担心 ImGuiLayer 内存泄漏
        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);
    }

    Application::~Application()
    {
        PC_PROFILE_FUNCTION();
        Renderer::Shutdown();
    }

    void Application::PushLayer(Layer* layer)
    {
        PC_PROFILE_FUNCTION();
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* overlay)
    {
        PC_PROFILE_FUNCTION();
        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }

    void Application::OnEvent(SDL_Event& e)
    {
        PC_PROFILE_FUNCTION();

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                m_Running = false;
            if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_CLOSE)
                m_Running = false;
        }

        for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
        {
            (*it)->OnEvent(e);
        }
    }

    void Application::Run()
    {
        PC_PROFILE_FUNCTION();

        while (m_Running)
        {
            PC_PROFILE_SCOPE("RunLoop");

            // 开始主循环
            float    time     = (float)SDL_GetTicks64();
            Timestep timestep = time - m_LastFrameTime;
            m_LastFrameTime   = time;

            // 处理事件循环
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                ImGui_ImplSDL2_ProcessEvent(&event);
                if (event.type == SDL_QUIT)
                    m_Running = false;
                if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE)
                    m_Running = false;
            }

            // 设置清屏
            RenderCommand::SetClearColor(SDL_GetRenderer((SDL_Window*)m_Window->GetNativeWindow()), 10, 10, 10, 255);
            RenderCommand::Clear(SDL_GetRenderer((SDL_Window*)m_Window->GetNativeWindow()));

            // LayerStack更新
            if (!m_Minimized)
            {
                {
                    PC_PROFILE_SCOPE("LayerStack OnUpdate");

                    for (Layer* layer : m_LayerStack)
                        layer->OnUpdate(timestep);
                }
            }

            // 全局监听
            // auto xy = Input::GetMousePosition();
            // PC_CORE_TRACE("{0}, {1}", xy.x, xy.y);

            // 更新渲染ImGui部分
            m_ImGuiLayer->Begin();
            {
                PC_PROFILE_SCOPE("LayerStack OnImGuiRender");

                for (auto layer : m_LayerStack)
                {
                    layer->OnImGuiRender();
                }
            }
            m_ImGuiLayer->End();

            // 渲染所有更新部分
            m_Window->OnUpdate();
        }
    }
} // namespace Pecan