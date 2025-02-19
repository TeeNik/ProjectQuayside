#pragma once

#include "Quayside/Layer.h"

namespace Quayside
{
    class QUAYSIDE_API ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUpdate() override;
        virtual void OnEvent(Event& Event) override;
        
    private:
        float Time = 0.0f;
    
    };
}
