#pragma once
#include "Quayside/Window.h"

namespace Quayside
{
    class GraphicsContext;
}

struct GLFWwindow;

namespace Quayside
{
    class WindowsWindow : public Window
    {
    public:
        WindowsWindow(const WindowProperties& Props);
        ~WindowsWindow() override;

        void OnUpdate() override;

        inline unsigned int GetWidth() const override { return Data.Width; }
        inline unsigned int GetHeight() const override { return Data.Height; }

        inline void SetEventCallback(const EventCallbackFunc& InCallback) override;
        void SetVSync(bool Enabled) override;
        bool IsVSync() const override;

        inline virtual void* GetNativeWindow() override { return Window; }

    private:
        virtual void Init(const WindowProperties& Props);
        virtual void Shutdown();

        GLFWwindow* Window;
        GraphicsContext* Context;

        struct WindowData
        {
            std::string Title;
            unsigned int Width;
            unsigned int Height;
            bool VSync;
            EventCallbackFunc EventCallback;
        };

        WindowData Data;
    };
}

