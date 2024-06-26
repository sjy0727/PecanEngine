#include "pcpch.h"

#include "Runtime/Core/Application.h"
#include "Runtime/ImGui/ImGuiLayer.h"

#include "imgui.h"
// #include <ImGui/imnodes.h>
// #include <ImGuizmo.h>

#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_sdlrenderer2.h"

#include "SDL.h"
#if !SDL_VERSION_ATLEAST(2, 0, 17)
#    error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

namespace Pecan
{

    ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {}

    ImGuiLayer::~ImGuiLayer() = default;

    void ImGuiLayer::OnAttach()
    {
        PC_PROFILE_FUNCTION();

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        // ImNodes::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO();
        (void)io;
        // io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        // io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        // const ImWchar my_ranges[]={
        //     0xC8AB,0xC6C1,
        //     0x3000,0x303F,
        //     0xFFFF,0xFFEF,
        //     0
        // };
        //
        // ImFontConfig config;
        // config.MergeMode = false;
        // config.GlyphRanges = my_ranges;
        //
        // io.Fonts->AddFontFromFileTTF("zpix.ttf", 12.0f, &config);
        // io.Fonts->AddFontFromFileTTF("zpix.ttf", 12.0f, nullptr,io.Fonts->GetGlyphRangesChineseFull());

        io.Fonts->AddFontFromFileTTF(
            "/Users/sunjunyi/CLionProjects/LiteGine-copy/LiteGine-Editor/assets/fonts/opensans/OpenSans-Bold.ttf",
            18.0f);
        io.FontDefault = io.Fonts->AddFontFromFileTTF(
            "/Users/sunjunyi/CLionProjects/LiteGine-copy/LiteGine-Editor/assets/fonts/opensans/OpenSans-Regular.ttf",
            18.0f);

        ImGui::StyleColorsDark();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular
        // ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding              = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }
        SetDarkThemeColors();

        Application& app = Application::Get();

        SDL_Window*   current_context  = static_cast<SDL_Window*>(app.GetWindow().GetNativeWindow());
        SDL_Renderer* current_renderer = SDL_GetRenderer(current_context);

        ImGui_ImplSDL2_InitForSDLRenderer(current_context, current_renderer);
        ImGui_ImplSDLRenderer2_Init(current_renderer);
        // const char* glsl_version = "#version 410";
        // ImGui_ImplOpenGL3_Init(glsl_version);
    }

    void ImGuiLayer::OnDetach()
    {
        PC_PROFILE_FUNCTION();

        // Cleanup
        ImGui_ImplSDLRenderer2_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        // ImNodes::DestroyContext();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::OnEvent(SDL_Event& e)
    {
        // ImGui 中的事件处理现在受到视口（viewport）的焦点和悬停状态的影响，会被正确地阻塞或不阻塞。
        //        if (m_BlockEvents)
        //        {
        //            ImGuiIO& io = ImGui::GetIO();
        //            e.Handled |= e.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;
        //            e.Handled |= e.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
        //        }

        ImGui_ImplSDL2_ProcessEvent(&e);
    }

    void ImGuiLayer::Begin()
    {
        PC_PROFILE_FUNCTION();

        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        // ImGuizmo::BeginFrame();
    }
    void ImGuiLayer::End()
    {
        PC_PROFILE_FUNCTION();

        ImGuiIO&     io  = ImGui::GetIO();
        Application& app = Application::Get();
        io.DisplaySize   = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

        ImGui::Render();

        SDL_Window*   current_context  = static_cast<SDL_Window*>(app.GetWindow().GetNativeWindow());
        SDL_Renderer* current_renderer = SDL_GetRenderer(current_context);

        SDL_RenderSetScale(current_renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), current_renderer);

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            // GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            // glfwMakeContextCurrent(current_context);
            SDL_UpdateWindowSurface(current_context);
        }
    }

    void ImGuiLayer::SetDarkThemeColors()
    {
        auto& colors              = ImGui::GetStyle().Colors;
        colors[ImGuiCol_WindowBg] = ImVec4 {0.1f, 0.105f, 0.11f, 1.0f};

        // Headers
        colors[ImGuiCol_Header]        = ImVec4 {0.2f, 0.205f, 0.21f, 1.0f};
        colors[ImGuiCol_HeaderHovered] = ImVec4 {0.3f, 0.305f, 0.31f, 1.0f};
        colors[ImGuiCol_HeaderActive]  = ImVec4 {0.15f, 0.1505f, 0.151f, 1.0f};

        // Buttons
        colors[ImGuiCol_Button]        = ImVec4 {0.2f, 0.205f, 0.21f, 1.0f};
        colors[ImGuiCol_ButtonHovered] = ImVec4 {0.3f, 0.305f, 0.31f, 1.0f};
        colors[ImGuiCol_ButtonActive]  = ImVec4 {0.15f, 0.1505f, 0.151f, 1.0f};

        // Frame BG
        colors[ImGuiCol_FrameBg]        = ImVec4 {0.2f, 0.205f, 0.21f, 1.0f};
        colors[ImGuiCol_FrameBgHovered] = ImVec4 {0.3f, 0.305f, 0.31f, 1.0f};
        colors[ImGuiCol_FrameBgActive]  = ImVec4 {0.15f, 0.1505f, 0.151f, 1.0f};

        // Tabs
        colors[ImGuiCol_Tab]                = ImVec4 {0.15f, 0.1505f, 0.151f, 1.0f};
        colors[ImGuiCol_TabHovered]         = ImVec4 {0.38f, 0.3805f, 0.381f, 1.0f};
        colors[ImGuiCol_TabActive]          = ImVec4 {0.28f, 0.2805f, 0.281f, 1.0f};
        colors[ImGuiCol_TabUnfocused]       = ImVec4 {0.15f, 0.1505f, 0.151f, 1.0f};
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4 {0.2f, 0.205f, 0.21f, 1.0f};

        // Title
        colors[ImGuiCol_TitleBg]          = ImVec4 {0.15f, 0.1505f, 0.151f, 1.0f};
        colors[ImGuiCol_TitleBgActive]    = ImVec4 {0.15f, 0.1505f, 0.151f, 1.0f};
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4 {0.15f, 0.1505f, 0.151f, 1.0f};
    }

} // namespace Pecan
