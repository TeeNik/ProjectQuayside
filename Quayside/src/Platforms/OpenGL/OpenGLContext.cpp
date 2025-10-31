#include "qspch.h"
#include "OpenGLContext.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>


namespace Quayside
{
    OpenGLContext::OpenGLContext(GLFWwindow* InWindowHandle) : WindowHandle(InWindowHandle)
    {
        QS_CORE_ASSERT(InWindowHandle, "Window handle is null");
    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(WindowHandle);
        int Status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        QS_CORE_ASSERT(Status, "Failed to initialize Glad!");

        QS_CORE_INFO("OpenGL Renderer: {0} {1}", (const char*)glGetString(GL_VERSION), (const char*)glGetString(GL_RENDERER));
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(WindowHandle);
    }
}
