#pragma once
#include "Quayside/Layer.h"

namespace Quayside
{
    class MouseScrolledEvent;
    class MouseMovedEvent;
    class MouseButtonPressedEvent;
    class WindowResizeEvent;
    class MouseButtonReleasedEvent;
    class KeyPressedEvent;
    class KeyReleasedEvent;
    class KeyTypedEvent;

    class QUAYSIDE_API ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnImGuiRender() override;

        void Begin();
        void End();
        
    private:
        float Time = 0.0f;
    };
}
