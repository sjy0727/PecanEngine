#pragma once

#include <sstream>

#include "Runtime/Core/Base.h"
#include "Runtime/Events/Event.h"

#include "SDL.h"

namespace Pecan
{
    struct WindowProps
    {
        std::string Title;
        uint32_t    Width;
        uint32_t    Height;

        // TODO: 更改引擎窗口大小
        WindowProps(const std::string& title = "Pecan", uint32_t width = 800, uint32_t height = 600) :
            Title(title), Width(width), Height(height)
        {}
    };

    class Window
    {
    private:
        virtual void Init(const WindowProps& props);
        virtual void Shutdown();

    private:
        SDL_Window* m_Window;
        // Scope<GraphicsContext> m_Context;

        struct WindowData
        {
            std::string  Title;
            unsigned int Width;
            unsigned int Height;
            bool         Vsync;

            std::function<void(SDL_Event&)> EventCallback;
        };

        WindowData m_Data;

    public:
        using EventCallbackFn = std::function<void(SDL_Event&)>;

        Window(const WindowProps& props);
        // FIXME: 析构函数改为纯虚函数
        ~Window();

        void OnUpdate();

        uint32_t GetWidth() const;
        uint32_t GetHeight() const;

        void SetEventCallback(const EventCallbackFn& callback);
        void SetVSync(bool enabled);
        bool IsVSync() const;

        void* GetNativeWindow() const;

        static Scope<Window> Create(const WindowProps& props = WindowProps());
    };

} // namespace Pecan