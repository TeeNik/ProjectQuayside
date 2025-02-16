#include "qspch.h"
#include "WindowsWindow.h"

#include "Quayside/Log.h"

namespace Quayside
{
    static bool bGLFWInitialized = false;

    Window* Window::Create(const WindowProperties& Props)
    {
        return new WindowsWindow(Props);
    }
    
    WindowsWindow::WindowsWindow(const WindowProperties& Props)
    {
        Init(Props);
    }

    WindowsWindow::~WindowsWindow()
    {
        Shutdown();
    }

    void WindowsWindow::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(Window);
    }

    void WindowsWindow::SetEventCallback(const EventCallbackFunc& InCallback)
    {
        Data.EventCallback = InCallback;
    }

    void WindowsWindow::SetVSync(bool Enabled)
    {
        glfwSwapInterval(Enabled ? 1 : 0);
        Data.VSync = Enabled;
    }

    bool WindowsWindow::IsVSync() const
    {
        return Data.VSync;
    }

    void WindowsWindow::Init(const WindowProperties& Props)
    {
        Data.Title = Props.Title;
        Data.Width = Props.Width;
        Data.Height = Props.Height;

        QS_CORE_INFO("Creating window {0} {1} {2}", Data.Title, Data.Width, Data.Height);

        if (!bGLFWInitialized)
        {
            int Success = glfwInit();
            QS_CORE_ASSERT(Success, "Failed to initialize GLFW");
            bGLFWInitialized = true;
        }

        Window = glfwCreateWindow(Data.Width, Data.Height, Data.Title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(Window);
        glfwSetWindowUserPointer(Window, &Data);
        SetVSync(true);
    }

    void WindowsWindow::Shutdown()
    {
        glfwDestroyWindow(Window);
    }
}


