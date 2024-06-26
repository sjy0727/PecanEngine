#pragma once

#include "Components.h"

namespace Pecan
{
    class PositionComponent : public Component
    {
    private:
        int xpos;
        int ypos;

    public:
        PositionComponent()
        {
            xpos = 0;
            ypos = 0;
        }

        PositionComponent(int x, int y)
        {
            xpos = x;
            ypos = y;
        }

        int x() { return xpos; }
        int y() { return ypos; }

        void OnAttach() override {}

        void OnUpdate(Timestep ts) override
        {
            xpos+=ts/10;
            ypos+=ts/10;
        }

        void SetPos(int x, int y)
        {
            xpos = x;
            ypos = y;
        }
    };
} // namespace Pecan