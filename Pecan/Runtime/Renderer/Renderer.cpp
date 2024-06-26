#include "pcpch.h"

#include "Runtime/Core/Application.h"
#include "Runtime/Renderer/Renderer.h"

#include "SDL.h"

namespace Pecan
{

    void Renderer::Init(SDL_Window* window, int index, Uint32 flags)
    {
        PC_PROFILE_FUNCTION();

        //        RenderCommand::Init();
        //        Renderer2D::Init();
        //        m_Renderer = CreateRef<SDL_Renderer>(SDL_CreateRenderer(window, index, flags));
        Application::SetRenderer(SDL_CreateRenderer(window, index, flags));
    }

    void Renderer::Shutdown()
    {
        // Renderer2D::Shutdown();
        SDL_DestroyRenderer(Application::GetRenderer());
    }

} // namespace Pecan