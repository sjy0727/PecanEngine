#pragma once

#include "Pecan.h"

#include "Runtime/ECS/Components.h"
#include "Runtime/ECS/ECS.h"

class Sandbox2D : public Pecan::Layer
{
public:
    Pecan::Manager m_Manager;

public:
    Sandbox2D(SDL_Renderer* renderer);
    ~Sandbox2D() override = default;

    void OnAttach() override;
    void OnDetach() override;

    void OnUpdate(Pecan::Timestep ts) override;
    void OnImGuiRender() override;
    void OnEvent(SDL_Event& e) override;

private:
    SDL_Renderer* m_Renderer;

    //    Pecan::Ref<Pecan::Texture2D> m_Player;
    Pecan::Ref<Pecan::TileMap2D> m_Map;

    Pecan::Entity& m_Player = m_Manager.AddEntity();

    //    glm::vec4 m_SquareColor = {0.2f, 0.3f, 0.8f, 1.0f};
};