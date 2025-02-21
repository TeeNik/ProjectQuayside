#include "qspch.h"
#include "ImGuiLayer.h"
#include "GLFW/glfw3.h"
#include "Platforms/OpenGL/ImGuiOpenGLRenderer.h"
#include "Quayside/Application.h"
#include "Quayside/Events/MouseEvent.h"
#include "Quayside/Events/KeyEvent.h"
#include "Quayside/Events/ApplicationEvent.h"

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
        EventDispatcher Dispatcher(Event);
        Dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FUNC(OnMouseButtonPressedEvent));
        Dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FUNC(OnMouseReleasedEvent));
        Dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FUNC(OnMouseMovedEvent));
        Dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FUNC(OnMouseScrolledEvent));
        Dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FUNC(OnWindowResizedEvent));
        Dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FUNC(OnKeyPressedEvent));
        Dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FUNC(OnKeyReleasedEvent));
        //Dispatcher.Dispatch<KeyTypedEvent>(BIND_EVENT_FUNC(OnKeyTypedEvent));
    }

    bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& Event)
    {
        ImGuiIO& IO = ImGui::GetIO();
        IO.MouseDown[Event.GetMouseButton()] = true;
        return false;
    }

    bool ImGuiLayer::OnMouseReleasedEvent(MouseButtonReleasedEvent& Event)
    {
        ImGuiIO& IO = ImGui::GetIO();
        IO.MouseDown[Event.GetMouseButton()] = false;
        return false;
    }

    bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& Event)
    {
        ImGuiIO& IO = ImGui::GetIO();
        IO.MousePos = ImVec2(Event.GetX(), Event.GetY());
        return false;
    }

    bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& Event)
    {
        ImGuiIO& IO = ImGui::GetIO();
        IO.MouseWheelH += Event.GetOffsetX();
        IO.MouseWheel += Event.GetOffsetY();
        return false;
    }

    bool ImGuiLayer::OnWindowResizedEvent(WindowResizeEvent& Event)
    {
        return false;
    }

    bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& Event)
    {
        return false;
    }

    bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& Event)
    {
        return false;
    }

    //bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& Event)
    //{
    //}
}
