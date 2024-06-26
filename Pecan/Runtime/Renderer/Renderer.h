#pragma once

// #include "Runtime/Renderer/OrthographicCamera.h"
// #include "Runtime/Renderer/RenderCommand.h"
// #include "Runtime/Renderer/Shader.h"
#include "SDL.h"

namespace Pecan
{
    class Renderer
    {
    public:
        static void Init(SDL_Window* window, int index, Uint32 flags);
        static void Shutdown();

        //        static void OnWindowResize(uint32_t width, uint32_t height);
        //        static void BeginScene(OrthographicCamera& camera);
        //        static void EndScene();
        //
        //        static void Submit(const Ref<Shader>&      shader,
        //                           const Ref<VertexArray>& vertexArray,
        //                           const glm::mat4&        transform = glm::mat4(1.0f));

        //        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

    private:
        //        struct SceneData
        //        {
        //            glm::mat4 ViewProjectionMatrix;
        //        };
        //
        //        static Scope<SceneData> s_SceneData;
    };
} // namespace Pecan