#pragma once
#include "WindowsWindow.h"
#include "GLFW/glfw3.h"
#include "Quayside/Input.h"

namespace Quayside
{
    class WindowsInput : public Input
    {
    protected:
        virtual bool IsKeyPressedImpl(int Keycode) override;
        virtual bool IsMouseButtonPressedImpl(int Button) override;
        virtual std::pair<float, float> GetMousePositionImpl() override;
        virtual float GetMouseXImpl() override;
        virtual float GetMouseYImpl() override;

        GLFWwindow* GetGLFWWindow();
    };
}
