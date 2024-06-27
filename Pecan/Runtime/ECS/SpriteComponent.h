#pragma once

#include "Components.h"

#include "SDL.h"

namespace Pecan
{
    class SpriteComponent : public Component
    {
    private:
        TransformComponent* transform;
        SDL_Texture*        texture;
        SDL_Rect            srcRect;
        SDL_Rect            dstRect;

    public:
        SpriteComponent() = default;

        SpriteComponent(const char* path) { SetTexture(path); }

        void SetTexture(const char* path)
        {
            texture = Pecan::RenderCommand::LoadTexture(Application::GetRenderer(), path);
        }

        void OnAttach() override
        {
            transform = &m_Entity->GetComponent<TransformComponent>();

            srcRect.x = srcRect.y = 0;
            srcRect.w = srcRect.h = 32;
            dstRect.w = dstRect.h = 64;
        }

        void OnUpdate(Timestep ts) override
        {
            dstRect.x = (int)transform->position.x;
            dstRect.y = (int)transform->position.y;
        }

        void Draw() override
        {
            Pecan::RenderCommand::RenderCopy(Application::GetRenderer(), texture, &srcRect, &dstRect);
        }
    };
} // namespace Pecan