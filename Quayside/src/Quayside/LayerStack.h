#pragma once
#include "Quayside/Core.h"
#include "Layer.h"

namespace Quayside
{
    class QUAYSIDE_API LayerStack
    {
    public:
        LayerStack();
        ~LayerStack();

        void PushLayer(Layer* Layer);
        void PushOverlay(Layer* Overlay);
        void PopLayer(Layer* Layer);
        void PopOverlay(Layer* Overlay);

        std::vector<Layer*>::iterator begin() { return Layers.begin(); }
        std::vector<Layer*>::iterator end() { return Layers.end(); }
        
    private:
        std::vector<Layer*> Layers;
        unsigned int LayerInsertIndex = 0;
    };
}


