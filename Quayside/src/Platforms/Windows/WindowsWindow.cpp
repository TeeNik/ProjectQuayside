#include "qspch.h"
#include "WindowsWindow.h"
#include "Quayside/Log.h"
#include "Quayside/Events/ApplicationEvent.h"
#include "Quayside/Events/KeyEvent.h"
#include "Quayside/Events/MouseEvent.h"
#include <GLFW/glfw3.h>
#include "Platforms/OpenGL/OpenGLContext.h"

namespace Quayside
{
    static bool bGLFWInitialized = false;

    static void GLFWErrorCallback(int Error, const char* Description)
    {
        QS_CORE_ERROR("GLFW Error ({0}): {1}", Error, Description);
    }

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
        Context->SwapBuffers();
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
            glfwSetErrorCallback(GLFWErrorCallback);
            bGLFWInitialized = true;
        }

        Window = glfwCreateWindow(Data.Width, Data.Height, Data.Title.c_str(), nullptr, nullptr);
        Context = new OpenGLContext(Window);
        Context->Init();

        glfwSetWindowUserPointer(Window, &Data);
        SetVSync(true);

        //set GLFW callbacks
        glfwSetWindowSizeCallback(Window, [](GLFWwindow* Window, int Width, int Height)
        {
            WindowData& Data = *static_cast<WindowData*>(glfwGetWindowUserPointer(Window));
            Data.Width = Width;
            Data.Height = Height;
            
            WindowResizeEvent Event(Width, Height);
            Data.EventCallback(Event);
        });

        glfwSetWindowCloseCallback(Window, [](GLFWwindow* Window)
        {
            WindowData& Data = *static_cast<WindowData*>(glfwGetWindowUserPointer(Window));
            WindowCloseEvent Event;
            Data.EventCallback(Event);
        });

        glfwSetKeyCallback(Window, [](GLFWwindow* Window, int Key, int Scancode, int Action, int Mods)
        {
            WindowData& Data = *static_cast<WindowData*>(glfwGetWindowUserPointer(Window));
            switch (Action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent PressedEvent(Key);
                    Data.EventCallback(PressedEvent);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent ReleasedEvent(Key);
                    Data.EventCallback(ReleasedEvent);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyHoldEvent HoldEvent(Key);
                    Data.EventCallback(HoldEvent);
                    break;
                }
            }
        });

        glfwSetCharCallback(Window, [](GLFWwindow* Window, unsigned int Character)
        {
            WindowData& Data = *static_cast<WindowData*>(glfwGetWindowUserPointer(Window));
            KeyTypedEvent TypedEvent(Character);
            Data.EventCallback(TypedEvent);
        });
        
        glfwSetMouseButtonCallback(Window, [](GLFWwindow* Window, int Button, int Action, int Mods)
        {
            WindowData& Data = *static_cast<WindowData*>(glfwGetWindowUserPointer(Window));
            switch (Action)
            {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent PressedEvent(Button);
                   Data.EventCallback(PressedEvent);
                   break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent ReleasedEvent(Button);
                   Data.EventCallback(ReleasedEvent);
                   break;
                }
            }
        });

        glfwSetScrollCallback(Window, [](GLFWwindow* Window, double OffsetX, double OffsetY)
        {
            WindowData& Data = *static_cast<WindowData*>(glfwGetWindowUserPointer(Window));
            MouseScrolledEvent Event(static_cast<float>(OffsetX), static_cast<float>(OffsetY));
            Data.EventCallback(Event);
        });

        glfwSetCursorPosCallback(Window, [](GLFWwindow* Window, double PosX, double PosY)
        {
            WindowData& Data = *static_cast<WindowData*>(glfwGetWindowUserPointer(Window));
            MouseMovedEvent Event(static_cast<float>(PosX), static_cast<float>(PosY));
            Data.EventCallback(Event);
        });
        
    }

    void WindowsWindow::Shutdown()
    {
        glfwDestroyWindow(Window);
    }
}


