#include "qspch.h"
#include "WindowsInput.h"
#include <GLFW/glfw3.h>
#include "Quayside/Application.h"

namespace Quayside
{
    bool WindowsInput::IsKeyPressedImpl(int Keycode)
    {
        auto* Window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        const auto State = glfwGetKey(Window, Keycode);
        return State == GLFW_PRESS || State == GLFW_REPEAT;
    }
}

