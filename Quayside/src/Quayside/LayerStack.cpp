#include "qspch.h"
#include "LayerStack.h"

namespace Quayside
{
    LayerStack::LayerStack()
    {
        LayerInsert = Layers.begin();
    }

    LayerStack::~LayerStack()
    {
        for (auto* Layer : Layers)
        {
            delete Layer;
        }
    }

    void LayerStack::PushLayer(Layer* Layer)
    {
        LayerInsert = Layers.emplace(LayerInsert, Layer);
    }

    void LayerStack::PushOverlay(Layer* Overlay)
    {
        Layers.emplace_back(Overlay);
    }

    void LayerStack::PopLayer(Layer* Layer)
    {
        if (auto it = std::find(Layers.begin(), Layers.end(), Layer); it != Layers.end())
        {
            Layers.erase(it);
            --LayerInsert;
        }
    }

    void LayerStack::PopOverlay(Layer* Overlay)
    {
        if (auto it = std::find(Layers.begin(), Layers.end(), Overlay); it != Layers.end())
        {
            Layers.erase(it);
        }
    }
}
