#pragma once

#include "pcpch.h"

#include "Runtime/Core/Base.h"
#include "Runtime/Core/Layer.h"

namespace Pecan
{
    class LayerStack
    {
    private:
        std::vector<Layer*> m_Layers;
        //        std::vector<Layer*>::iterator m_LayerInsert;
        unsigned int m_LayerInsertIndex = 0;

    public:
        LayerStack() = default;
        ~LayerStack();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
        void PopLayer(Layer* layer);
        void PopOverlay(Layer* overlay);

        std::vector<Layer*>::iterator               begin() { return m_Layers.begin(); }
        std::vector<Layer*>::iterator               end() { return m_Layers.end(); }
        std::vector<Layer*>::reverse_iterator       rbegin() { return m_Layers.rbegin(); }
        std::vector<Layer*>::reverse_iterator       rend() { return m_Layers.rend(); }
        std::vector<Layer*>::const_iterator         begin() const { return m_Layers.begin(); }
        std::vector<Layer*>::const_iterator         end() const { return m_Layers.end(); }
        std::vector<Layer*>::const_reverse_iterator rbegin() const { return m_Layers.rbegin(); }
        std::vector<Layer*>::const_reverse_iterator rend() const { return m_Layers.rend(); }
    };
} // namespace Pecan