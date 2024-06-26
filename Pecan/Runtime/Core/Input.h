#pragma once

#include "pcpch.h"

// #include <glm/glm.hpp>

#include "Runtime/Core/KeyCodes.h"
#include "Runtime/Core/MouseCodes.h"

namespace Pecan
{
    class Input
    {
    protected:
        Input() = default;

    public:
        virtual ~Input() = default;

        Input(const Input&)            = delete;
        Input& operator=(const Input&) = delete;

        inline static bool IsKeyPressed(KeyCode key) { return s_Instance->IsKeyPressedImpl(key); }

        inline static bool IsMouseButtonPressed(MouseCode button)
        {
            return s_Instance->IsMouseButtonPressedImpl(button);
        }
        inline static std::pair<int, int> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
        inline static float               GetMouseX() { return s_Instance->GetMouseXImpl(); }
        inline static float               GetMouseY() { return s_Instance->GetMouseYImpl(); }

    protected:
        virtual bool                IsKeyPressedImpl(KeyCode keycode)          = 0;
        virtual bool                IsMouseButtonPressedImpl(MouseCode button) = 0;
        virtual std::pair<int, int> GetMousePositionImpl()                     = 0;
        virtual float               GetMouseXImpl()                            = 0;
        virtual float               GetMouseYImpl()                            = 0;

    private:
        static Scope<Input> s_Instance;
    };
} // namespace Pecan