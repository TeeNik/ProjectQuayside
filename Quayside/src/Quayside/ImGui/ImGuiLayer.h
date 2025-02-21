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
        virtual void OnUpdate() override;
        virtual void OnEvent(Event& Event) override;
        
    private:
        bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& Event);
        bool OnMouseReleasedEvent(MouseButtonReleasedEvent& Event);
        bool OnMouseMovedEvent(MouseMovedEvent& Event);
        bool OnMouseScrolledEvent(MouseScrolledEvent& Event);
        bool OnWindowResizedEvent(WindowResizeEvent& Event);
        bool OnKeyPressedEvent(KeyPressedEvent& Event);
        bool OnKeyReleasedEvent(KeyReleasedEvent& Event);
        bool OnKeyTypedEvent(KeyTypedEvent& Event);
        

        float Time = 0.0f;
    };
}
