#pragma once

#include "Components.h"

#include "SDL.h"

namespace Pecan
{
    class SpriteComponent : public Component
    {
    private:
        PositionComponent* position;
        SDL_Texture*       texture;
        SDL_Rect           srcRect;
        SDL_Rect           dstRect;

    public:
        SpriteComponent() = default;

        SpriteComponent(const char* path) { SetTexture(path); }

        void SetTexture(const char* path)
        {
            texture = Pecan::RenderCommand::LoadTexture(Application::GetRenderer(), path);
        }

        void OnAttach() override
        {
            position = &m_Entity->GetComponent<PositionComponent>();

            srcRect.x = srcRect.y = 0;
            srcRect.w = srcRect.h = 32;
            dstRect.w = dstRect.h = 64;
        }

        void OnUpdate(Timestep ts) override
        {
            dstRect.x = position->x();
            dstRect.y = position->y();
        }

        void Draw() override
        {
            Pecan::RenderCommand::RenderCopy(Application::GetRenderer(), texture, &srcRect, &dstRect);
        }
    };
} // namespace Pecan