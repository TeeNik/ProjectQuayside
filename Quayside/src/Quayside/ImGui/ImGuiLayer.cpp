#include "qspch.h"
#include "ImGuiLayer.h"
#include "Quayside/Application.h"

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"

//TEMPORARY
#include "GLFW/glfw3.h"

namespace Quayside
{
    ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer")
    {
    }

    ImGuiLayer::~ImGuiLayer()
    {
    }

    void ImGuiLayer::OnAttach()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& IO = ImGui::GetIO();
        IO.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        //IO.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
        IO.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        IO.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        //IO.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
        //IO.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;
        
        //IO.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        //IO.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
        
        ImGui::StyleColorsDark();
        ImGuiStyle& Style = ImGui::GetStyle();
        if (IO.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            Style.WindowRounding = 0.0f;
            Style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        Application& App = Application::Get();
        GLFWwindow* Window = static_cast<GLFWwindow*>(App.GetWindow().GetNativeWindow());

        ImGui_ImplGlfw_InitForOpenGL(Window, true);
        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImGuiLayer::OnDetach()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::Begin()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayer::End()
    {
        ImGuiIO& IO = ImGui::GetIO();
        Application& App = Application::Get();
        IO.DisplaySize = ImVec2((float)App.GetWindow().GetWidth(), (float)App.GetWindow().GetHeight());

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (IO.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* BackupCurrentContext = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(BackupCurrentContext);
        }
    }

    void ImGuiLayer::OnImGuiRender()
    {
        static bool Show = true;
        ImGui::ShowDemoWindow(&Show);
    }
}
