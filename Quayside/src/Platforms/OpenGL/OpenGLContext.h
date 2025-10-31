#pragma once
#include "Quayside/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Quayside
{
    class OpenGLContext : public GraphicsContext
    {
    public:
        OpenGLContext(GLFWwindow* InWindowHandle);
        
        virtual void Init() override;
        virtual void SwapBuffers() override;
    private:
        GLFWwindow* WindowHandle;
    };
}


