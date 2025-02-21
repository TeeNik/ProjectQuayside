#pragma once
#include "Event.h"

namespace Quayside
{
    class QUAYSIDE_API KeyEvent : public Event
    {
    public:
        inline int GetKeyCode() const {return KeyCode;}

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << GetName() << ": " << GetKeyCode();
            return ss.str();
        }
        
    protected:
        KeyEvent(int InKeyCode) : KeyCode(InKeyCode) {}
        
        int KeyCode;
    };

    class QUAYSIDE_API KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(int InKeyCode) : KeyEvent(InKeyCode) {}
        EVENT_CLASS_TYPE(KeyPressed)
    };

    class QUAYSIDE_API KeyHoldEvent : public KeyEvent
    {
    public:
        KeyHoldEvent(int InKeyCode) : KeyEvent(InKeyCode) {}
        EVENT_CLASS_TYPE(KeyHold)
    };

    class QUAYSIDE_API KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(int InKeyCode) : KeyEvent(InKeyCode) {}
        EVENT_CLASS_TYPE(KeyReleased)
    };

    class QUAYSIDE_API KeyTypedEvent : public KeyEvent
    {
    public:
        KeyTypedEvent(int InKeyCode) : KeyEvent(InKeyCode) {}
        EVENT_CLASS_TYPE(KeyTyped)
    };
}
