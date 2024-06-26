#pragma once

#include "Runtime/Core/Base.h"
#include "Runtime/Core/Timestep.h"
#include "Runtime/Events/Event.h"

#include "SDL.h"

namespace Pecan
{
    class Layer
    {
    protected:
        std::string m_DebugName;

    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer();

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(Timestep ts) {}
        virtual void OnImGuiRender() {}
        virtual void OnEvent(SDL_Event& event) {}
        // virtual void OnEvent(Event& event) {}

        inline const std::string& GetName() const { return m_DebugName; }
    };
} // namespace Pecan