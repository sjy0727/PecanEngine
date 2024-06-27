// #include "pcpch.h"

#include "Sandbox2D.h"

#include "imgui.h"

#include "SDL.h"

Sandbox2D::Sandbox2D(SDL_Renderer* renderer) : Layer("Sandbox2D"), m_Renderer(renderer) {}

void Sandbox2D::OnAttach()
{
    PC_PROFILE_FUNCTION();

    m_Map = Pecan::TileMap2D::Create();

    m_Player.AddComponent<Pecan::TransformComponent>(0, 0);
    m_Player.AddComponent<Pecan::SpriteComponent>("../../assets/sprites/knight.png");
}

void Sandbox2D::OnDetach() { PC_PROFILE_FUNCTION(); }

void Sandbox2D::OnUpdate(Pecan::Timestep ts)
{
    PC_PROFILE_FUNCTION();

    m_Map->RenderCopy();

    //    // 图像的原始尺寸与位置
    //    m_Player->m_SrcRect.h = 32;
    //    m_Player->m_SrcRect.w = 32;
    //    m_Player->m_SrcRect.x = 0;
    //    m_Player->m_SrcRect.y = 0;
    //
    //    // 最终显示图像的尺寸与位置
    //    m_Player->m_DstRect.x = 0;
    //    m_Player->m_DstRect.y = 0;
    //    m_Player->m_DstRect.w = m_Player->m_SrcRect.w * 2;
    //    m_Player->m_DstRect.h = m_Player->m_SrcRect.h * 2;
    //
    //    m_Player->RenderCopy(m_Player->m_SrcRect, m_Player->m_DstRect);

    m_Manager.Refresh();
    m_Manager.OnUpdate(ts);

    m_Player.GetComponent<Pecan::TransformComponent>().velocity = Pecan::Vector2D(1, 1);

    if (m_Player.GetComponent<Pecan::TransformComponent>().position.x > 400)
    {
        m_Player.GetComponent<Pecan::SpriteComponent>().SetTexture("../../assets/sprites/fruit.png");
    }

    m_Manager.Draw();

    //    PC_TRACE("Position ({0}, {1})",
    //             m_Player.GetComponent<Pecan::PositionComponent>().x(),
    //             m_Player.GetComponent<Pecan::PositionComponent>().y());

#if 0
    Pecan::RenderCommand::SetClearColor(m_Renderer, 110, 110, 110, 255);
    Pecan::RenderCommand::Clear(m_Renderer);
#endif

    //
    //    // Update
    //    m_CameraController.OnUpdate(ts);
    //
    //    // Render
    //    Pecan::Renderer2D::ResetStats();
    //    {
    //        PC_PROFILE_FUNCTION("Renderer Prep");
    //        Pecan::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    //        Pecan::RenderCommand::Clear();
    //    }
    //
    //    {
    //        static float rotation = 0.0f;
    //        rotation += ts * 50.0f;
    //
    //        PC_PROFILE_SCOPE("Renderer Draw");
    //        Pecan::Renderer2D::BeginScene(m_CameraController.GetCamera());
    //        Pecan::Renderer2D::DrawRotatedQuad({1.0f, 0.0f}, {0.8f, 0.8f}, -45.0f, {0.8f, 0.2f, 0.3f, 1.0f});
    //        Pecan::Renderer2D::DrawQuad({-1.0f, 0.0f}, {0.8f, 0.8f}, {0.8f, 0.2f, 0.3f, 1.0f});
    //        Pecan::Renderer2D::DrawQuad({0.5f, -0.5f}, {0.5f, 0.75f}, m_SquareColor);
    //        Pecan::Renderer2D::DrawQuad({0.0f, 0.0f, -0.1f}, {20.0f, 20.0f}, m_CheckerboardTexture, 10.0f);
    //        Pecan::Renderer2D::DrawRotatedQuad({-2.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, rotation,
    //        m_CheckerboardTexture, 20.0f); Pecan::Renderer2D::EndScene();
    //
    //        // 彩虹棋盘
    //        Pecan::Renderer2D::BeginScene(m_CameraController.GetCamera());
    //        for (float y = -5.0f; y < 5.0f; y += 0.5f)
    //        {
    //            for (float x = -5.0f; x < 5.0f; x += 0.5f)
    //            {
    //                glm::vec4 color = {(x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f};
    //                LiteGine::Renderer2D::DrawQuad({x, y}, {0.45f, 0.45f}, color);
    //            }
    //        }
    //        Pecan::Renderer2D::EndScene();
    //    }
    //
    //    // TODO: Add these functions - Shader::SetMat4, Shader::SetFloat4
    //    // std::dynamic_pointer_cast<LiteGine::OpenGLShader>(m_FlatColorShader)->Bind();
    //    // std::dynamic_pointer_cast<LiteGine::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color",
    //    // m_SquareColor);
}

void Sandbox2D::OnImGuiRender()
{
    PC_PROFILE_FUNCTION();

    //        ImGui::Begin("Settings");
    //        ImGui::Text("Renderer2D Stats:");
    //        ImGui::End();
    //
    //        ImGui::Begin("Hello");
    //        ImGui::Text("World");
    //        ImGui::End();
}

void Sandbox2D::OnEvent(SDL_Event& e)
{
    //    m_CameraController.OnEvent(e);
}