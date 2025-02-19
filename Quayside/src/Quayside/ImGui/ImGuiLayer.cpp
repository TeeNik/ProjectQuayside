#include "qspch.h"
#include "ImGuiLayer.h"
#include "GLFW/glfw3.h"
#include "Platforms/OpenGL/ImGuiOpenGLRenderer.h"
#include "Quayside/Application.h"

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
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& IO = ImGui::GetIO();
        IO.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        IO.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImGuiLayer::OnDetach()
    {
    }

    void ImGuiLayer::OnUpdate()
    {
        ImGuiIO& IO = ImGui::GetIO();
        Application& App = Application::Get();
        IO.DisplaySize = ImVec2(App.GetWindow().GetWidth(), App.GetWindow().GetHeight());
        
        float FrameTime = static_cast<float>(glfwGetTime());
        IO.DeltaTime = Time > 0.0f ? (FrameTime - Time) : (1.0f / 60.0f);
        Time = FrameTime;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();
        
        static bool Show = true;
        ImGui::ShowDemoWindow(&Show);
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::OnEvent(Event& Event)
    {
    }
}
