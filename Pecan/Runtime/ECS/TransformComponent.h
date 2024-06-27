#pragma once

#include "Components.h"

#include "Runtime/Math/Vector2D.h"

namespace Pecan
{
    struct TransformComponent : public Component
    {
    public:
        Vector2D position;
        Vector2D velocity;

        int speed = 3;

        TransformComponent() { SetPos(0.0f, 0.0f); }

        TransformComponent(float x, float y) { SetPos(x, y); }

        // float x() { return position.x; }
        // float y() { return position.y; }

        void OnAttach() override
        {
            velocity.x = 0;
            velocity.y = 0;
        }

        void OnUpdate(Timestep ts) override
        {
            position.x += velocity.x * speed;
            position.y += velocity.y * speed;
        }

        void SetPos(float x, float y)
        {
            position.x = x;
            position.y = y;
        }
    };
} // namespace Pecan