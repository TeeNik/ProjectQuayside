#pragma once
#include "Events/Event.h"

namespace Quayside
{
    struct WindowProperties
    {
        std::string Title;
        unsigned int Width;
        unsigned int Height;

        WindowProperties(const std::string& Title = "Quayside Engine", unsigned int Width = 1280, unsigned int Height = 720) : Title(Title), Width(Width), Height(Height) {}
    };
    
    class QUAYSIDE_API Window
    {
    public:
        using EventCallbackFunc = std::function<void(Quayside::Event&)>;

        virtual ~Window() = default;

        virtual void OnUpdate() = 0;

        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;

        virtual void SetEventCallback(const EventCallbackFunc& InCallback) = 0;
        virtual void SetVSync(bool InVSync) = 0;
        virtual bool IsVSync() const = 0;

        static Window* Create(const WindowProperties& Props = WindowProperties());
    };
}


