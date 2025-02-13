#pragma once

#include "Event.h"

namespace Quayside
{
    class QUAYSIDE_API MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(float X, float Y) : MouseX(X), MouseY(Y) {}

        inline float GetX() const { return MouseX; }
        inline float GetY() const { return MouseY; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << GetX() << ", " << GetY();
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    private:
        float MouseX, MouseY;
    };

    class QUAYSIDE_API MouseScrolledEvent : public Event
    {
    public:
        MouseScrolledEvent(float InOffsetX, float InOffsetY) : OffsetX(InOffsetX), OffsetY(InOffsetY) {}

        inline float GetOffsetX() const { return OffsetX; }
        inline float GetOffsetY() const { return OffsetY; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << GetOffsetX() << ", " << GetOffsetY();
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseScrolled)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
    
    private:
        float OffsetX, OffsetY;
    };

    class QUAYSIDE_API MouseButtonEvent : public Event
    {
    public:
        inline int GetMouseButton() const { return Button; }

        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
    protected:
        MouseButtonEvent(int InButton) : Button(InButton) {}

        int Button;
    };

    class QUAYSIDE_API MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(int InButton) : MouseButtonEvent(InButton) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << Button;
            return ss.str();
        }
        
        EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    class QUAYSIDE_API MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(int InButton) : MouseButtonEvent(InButton) {}
        
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << Button;
            return ss.str();
        }
        
        EVENT_CLASS_TYPE(MouseButtonReleased)
    };
}
