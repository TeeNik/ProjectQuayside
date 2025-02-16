#pragma once
#include "Event.h"

namespace Quayside
{
    class QUAYSIDE_API WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(int InWidth, int InHeight) : Width(InWidth), Height(InHeight) {}

        inline unsigned int GetWidth() const { return Width; }
        inline unsigned int GetHeight() const { return Height; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << Width << ", " << Height;
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResize)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)

    private:
        unsigned int Width, Height;
    };
    
    class QUAYSIDE_API WindowCloseEvent : public Event
    {
    public:
        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class QUAYSIDE_API AppTickEvent : public Event
    {
    public:
        EVENT_CLASS_TYPE(AppTick)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class QUAYSIDE_API AppRenderEvent : public Event
    {
    public:
        EVENT_CLASS_TYPE(AppRender)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };
}
