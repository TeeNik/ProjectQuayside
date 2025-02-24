#include "qspch.h"
#include "WindowsInput.h"
#include <GLFW/glfw3.h>
#include "Quayside/Application.h"

namespace Quayside
{
    Input* Input::Instance = new WindowsInput();
    
    bool WindowsInput::IsKeyPressedImpl(int Keycode)
    {
        const auto State = glfwGetKey(GetGLFWWindow(), Keycode);
        return State == GLFW_PRESS || State == GLFW_REPEAT;
    }

    bool WindowsInput::IsMouseButtonPressedImpl(int Button)
    {
        const auto State = glfwGetMouseButton(GetGLFWWindow(), Button);
        return State == GLFW_PRESS;
    }

    std::pair<float, float> WindowsInput::GetMousePositionImpl()
    {
        double PosX, PosY;
        glfwGetCursorPos(GetGLFWWindow(), &PosX, &PosY);
        return {PosX, PosY};
    }

    float WindowsInput::GetMouseXImpl()
    {
        return GetMousePositionImpl().first;
    }

    float WindowsInput::GetMouseYImpl()
    {
        return GetMousePositionImpl().second;
    }

    GLFWwindow* WindowsInput::GetGLFWWindow()
    {
        return static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
    }
}

