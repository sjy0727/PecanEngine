#include "pcpch.h"

#include "Runtime/Core/Assert.h"
#include "Runtime/Core/Input.h"
#include "Runtime/Core/Window.h"

#include "Runtime/Events/ApplicationEvent.h"
#include "Runtime/Events/KeyEvent.h"
#include "Runtime/Events/MouseEvent.h"

#include "Runtime/Renderer/Renderer.h"

namespace Pecan
{
    static uint8_t s_SDLWindowCount = 0;

    Scope<Window> Window::Create(const WindowProps& props) { return CreateScope<Window>(props); }

    Window::Window(const WindowProps& props)
    {
        PC_PROFILE_FUNCTION();
        Init(props);
    }

    Window::~Window()
    {
        PC_PROFILE_FUNCTION();
        Shutdown();
    }

    void Window::Init(const WindowProps& props)
    {
        PC_PROFILE_FUNCTION();

        m_Data.Title  = props.Title;
        m_Data.Height = props.Height;
        m_Data.Width  = props.Width;

        PC_CORE_INFO("Creating window \"{0}\"! Size: ({1}, {2})", props.Title, props.Width, props.Height);

        if (s_SDLWindowCount == 0)
        {
            PC_PROFILE_SCOPE("SDLInit");

            int success = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER);
            PC_CORE_ASSERT(success, SDL_GetError());
        }

// From 2.0.18: Enable native IME.
#ifdef SDL_HINT_IME_SHOW_UI
        SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif

        {
            PC_PROFILE_SCOPE("SDLCreateWindow");

            SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
            m_Window                     = SDL_CreateWindow(m_Data.Title.c_str(),
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        (int)props.Width,
                                        (int)props.Height,
                                        window_flags);

            ++s_SDLWindowCount;
        }

        SetVSync(true);
    }

    void Window::Shutdown()
    {
        PC_PROFILE_FUNCTION();

        SDL_DestroyWindow(m_Window);

        s_SDLWindowCount -= 1;
        if (s_SDLWindowCount == 0)
        {
            PC_CORE_INFO("Terminating SDL");
            //            glfwTerminate();
            SDL_Quit();
        }
    }

    void Window::OnUpdate()
    {
        PC_PROFILE_FUNCTION();

        // glfwPollEvents();
        SDL_Event event;
        SDL_PollEvent(&event);

        SDL_RenderPresent(SDL_GetRenderer(m_Window));
    }

    void Window::SetVSync(bool enabled)
    {
        PC_PROFILE_FUNCTION();

        // glfwSwapInterval(enabled ? 1 : 0);
        SDL_RenderSetVSync(SDL_GetRenderer(m_Window), (int)enabled);
        m_Data.Vsync = enabled;
    }

    void Window::SetEventCallback(const EventCallbackFn& callback) {}

    bool Window::IsVSync() const { return m_Data.Vsync; }

    void* Window::GetNativeWindow() const { return m_Window; }

    uint32_t Window::GetWidth() const { return m_Data.Width; }
    uint32_t Window::GetHeight() const { return m_Data.Height; }

} // namespace Pecan