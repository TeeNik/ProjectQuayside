﻿#include "qspch.h"
#include "ImGuiLayer.h"
#include "Platforms/OpenGL/ImGuiOpenGLRenderer.h"
#include "Quayside/Application.h"
#include "Quayside/Events/MouseEvent.h"
#include "Quayside/Events/KeyEvent.h"
#include "Quayside/Events/ApplicationEvent.h"
#include <GL/gl.h>

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
        Dispatcher.Dispatch<KeyTypedEvent>(BIND_EVENT_FUNC(OnKeyTypedEvent));
    }

    ImGuiKey GlfwKeyToImGuiKey(int keycode)
    {
        switch (keycode)
        {
            case GLFW_KEY_TAB: return ImGuiKey_Tab;
            case GLFW_KEY_LEFT: return ImGuiKey_LeftArrow;
            case GLFW_KEY_RIGHT: return ImGuiKey_RightArrow;
            case GLFW_KEY_UP: return ImGuiKey_UpArrow;
            case GLFW_KEY_DOWN: return ImGuiKey_DownArrow;
            case GLFW_KEY_PAGE_UP: return ImGuiKey_PageUp;
            case GLFW_KEY_PAGE_DOWN: return ImGuiKey_PageDown;
            case GLFW_KEY_HOME: return ImGuiKey_Home;
            case GLFW_KEY_END: return ImGuiKey_End;
            case GLFW_KEY_INSERT: return ImGuiKey_Insert;
            case GLFW_KEY_DELETE: return ImGuiKey_Delete;
            case GLFW_KEY_BACKSPACE: return ImGuiKey_Backspace;
            case GLFW_KEY_SPACE: return ImGuiKey_Space;
            case GLFW_KEY_ENTER: return ImGuiKey_Enter;
            case GLFW_KEY_ESCAPE: return ImGuiKey_Escape;
            case GLFW_KEY_APOSTROPHE: return ImGuiKey_Apostrophe;
            case GLFW_KEY_COMMA: return ImGuiKey_Comma;
            case GLFW_KEY_MINUS: return ImGuiKey_Minus;
            case GLFW_KEY_PERIOD: return ImGuiKey_Period;
            case GLFW_KEY_SLASH: return ImGuiKey_Slash;
            case GLFW_KEY_SEMICOLON: return ImGuiKey_Semicolon;
            case GLFW_KEY_EQUAL: return ImGuiKey_Equal;
            case GLFW_KEY_LEFT_BRACKET: return ImGuiKey_LeftBracket;
            case GLFW_KEY_BACKSLASH: return ImGuiKey_Backslash;
            case GLFW_KEY_WORLD_1: return ImGuiKey_Oem102;
            case GLFW_KEY_WORLD_2: return ImGuiKey_Oem102;
            case GLFW_KEY_RIGHT_BRACKET: return ImGuiKey_RightBracket;
            case GLFW_KEY_GRAVE_ACCENT: return ImGuiKey_GraveAccent;
            case GLFW_KEY_CAPS_LOCK: return ImGuiKey_CapsLock;
            case GLFW_KEY_SCROLL_LOCK: return ImGuiKey_ScrollLock;
            case GLFW_KEY_NUM_LOCK: return ImGuiKey_NumLock;
            case GLFW_KEY_PRINT_SCREEN: return ImGuiKey_PrintScreen;
            case GLFW_KEY_PAUSE: return ImGuiKey_Pause;
            case GLFW_KEY_KP_0: return ImGuiKey_Keypad0;
            case GLFW_KEY_KP_1: return ImGuiKey_Keypad1;
            case GLFW_KEY_KP_2: return ImGuiKey_Keypad2;
            case GLFW_KEY_KP_3: return ImGuiKey_Keypad3;
            case GLFW_KEY_KP_4: return ImGuiKey_Keypad4;
            case GLFW_KEY_KP_5: return ImGuiKey_Keypad5;
            case GLFW_KEY_KP_6: return ImGuiKey_Keypad6;
            case GLFW_KEY_KP_7: return ImGuiKey_Keypad7;
            case GLFW_KEY_KP_8: return ImGuiKey_Keypad8;
            case GLFW_KEY_KP_9: return ImGuiKey_Keypad9;
            case GLFW_KEY_KP_DECIMAL: return ImGuiKey_KeypadDecimal;
            case GLFW_KEY_KP_DIVIDE: return ImGuiKey_KeypadDivide;
            case GLFW_KEY_KP_MULTIPLY: return ImGuiKey_KeypadMultiply;
            case GLFW_KEY_KP_SUBTRACT: return ImGuiKey_KeypadSubtract;
            case GLFW_KEY_KP_ADD: return ImGuiKey_KeypadAdd;
            case GLFW_KEY_KP_ENTER: return ImGuiKey_KeypadEnter;
            case GLFW_KEY_KP_EQUAL: return ImGuiKey_KeypadEqual;
            case GLFW_KEY_LEFT_SHIFT: return ImGuiKey_LeftShift;
            case GLFW_KEY_LEFT_CONTROL: return ImGuiKey_LeftCtrl;
            case GLFW_KEY_LEFT_ALT: return ImGuiKey_LeftAlt;
            case GLFW_KEY_LEFT_SUPER: return ImGuiKey_LeftSuper;
            case GLFW_KEY_RIGHT_SHIFT: return ImGuiKey_RightShift;
            case GLFW_KEY_RIGHT_CONTROL: return ImGuiKey_RightCtrl;
            case GLFW_KEY_RIGHT_ALT: return ImGuiKey_RightAlt;
            case GLFW_KEY_RIGHT_SUPER: return ImGuiKey_RightSuper;
            case GLFW_KEY_MENU: return ImGuiKey_Menu;
            case GLFW_KEY_0: return ImGuiKey_0;
            case GLFW_KEY_1: return ImGuiKey_1;
            case GLFW_KEY_2: return ImGuiKey_2;
            case GLFW_KEY_3: return ImGuiKey_3;
            case GLFW_KEY_4: return ImGuiKey_4;
            case GLFW_KEY_5: return ImGuiKey_5;
            case GLFW_KEY_6: return ImGuiKey_6;
            case GLFW_KEY_7: return ImGuiKey_7;
            case GLFW_KEY_8: return ImGuiKey_8;
            case GLFW_KEY_9: return ImGuiKey_9;
            case GLFW_KEY_A: return ImGuiKey_A;
            case GLFW_KEY_B: return ImGuiKey_B;
            case GLFW_KEY_C: return ImGuiKey_C;
            case GLFW_KEY_D: return ImGuiKey_D;
            case GLFW_KEY_E: return ImGuiKey_E;
            case GLFW_KEY_F: return ImGuiKey_F;
            case GLFW_KEY_G: return ImGuiKey_G;
            case GLFW_KEY_H: return ImGuiKey_H;
            case GLFW_KEY_I: return ImGuiKey_I;
            case GLFW_KEY_J: return ImGuiKey_J;
            case GLFW_KEY_K: return ImGuiKey_K;
            case GLFW_KEY_L: return ImGuiKey_L;
            case GLFW_KEY_M: return ImGuiKey_M;
            case GLFW_KEY_N: return ImGuiKey_N;
            case GLFW_KEY_O: return ImGuiKey_O;
            case GLFW_KEY_P: return ImGuiKey_P;
            case GLFW_KEY_Q: return ImGuiKey_Q;
            case GLFW_KEY_R: return ImGuiKey_R;
            case GLFW_KEY_S: return ImGuiKey_S;
            case GLFW_KEY_T: return ImGuiKey_T;
            case GLFW_KEY_U: return ImGuiKey_U;
            case GLFW_KEY_V: return ImGuiKey_V;
            case GLFW_KEY_W: return ImGuiKey_W;
            case GLFW_KEY_X: return ImGuiKey_X;
            case GLFW_KEY_Y: return ImGuiKey_Y;
            case GLFW_KEY_Z: return ImGuiKey_Z;
            case GLFW_KEY_F1: return ImGuiKey_F1;
            case GLFW_KEY_F2: return ImGuiKey_F2;
            case GLFW_KEY_F3: return ImGuiKey_F3;
            case GLFW_KEY_F4: return ImGuiKey_F4;
            case GLFW_KEY_F5: return ImGuiKey_F5;
            case GLFW_KEY_F6: return ImGuiKey_F6;
            case GLFW_KEY_F7: return ImGuiKey_F7;
            case GLFW_KEY_F8: return ImGuiKey_F8;
            case GLFW_KEY_F9: return ImGuiKey_F9;
            case GLFW_KEY_F10: return ImGuiKey_F10;
            case GLFW_KEY_F11: return ImGuiKey_F11;
            case GLFW_KEY_F12: return ImGuiKey_F12;
            case GLFW_KEY_F13: return ImGuiKey_F13;
            case GLFW_KEY_F14: return ImGuiKey_F14;
            case GLFW_KEY_F15: return ImGuiKey_F15;
            case GLFW_KEY_F16: return ImGuiKey_F16;
            case GLFW_KEY_F17: return ImGuiKey_F17;
            case GLFW_KEY_F18: return ImGuiKey_F18;
            case GLFW_KEY_F19: return ImGuiKey_F19;
            case GLFW_KEY_F20: return ImGuiKey_F20;
            case GLFW_KEY_F21: return ImGuiKey_F21;
            case GLFW_KEY_F22: return ImGuiKey_F22;
            case GLFW_KEY_F23: return ImGuiKey_F23;
            case GLFW_KEY_F24: return ImGuiKey_F24;
            default: return ImGuiKey_None;
        }
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
        ImGuiIO& IO = ImGui::GetIO();
        IO.DisplaySize = ImVec2(Event.GetWidth(), Event.GetHeight());
        IO.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
        glViewport(0, 0, Event.GetWidth(), Event.GetHeight());
        return false;
    }

    bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& Event)
    {
        ImGuiIO& IO = ImGui::GetIO();
        IO.AddKeyEvent(GlfwKeyToImGuiKey(Event.GetKeyCode()), true);
        IO.KeyCtrl = ImGui::IsKeyDown(GlfwKeyToImGuiKey(GLFW_KEY_LEFT_CONTROL)) || ImGui::IsKeyDown(GlfwKeyToImGuiKey(GLFW_KEY_RIGHT_CONTROL));
        IO.KeyShift = ImGui::IsKeyDown(GlfwKeyToImGuiKey(GLFW_KEY_LEFT_SHIFT)) || ImGui::IsKeyDown(GlfwKeyToImGuiKey(GLFW_KEY_RIGHT_SHIFT));
        IO.KeyAlt = ImGui::IsKeyDown(GlfwKeyToImGuiKey(GLFW_KEY_LEFT_ALT)) || ImGui::IsKeyDown(GlfwKeyToImGuiKey(GLFW_KEY_RIGHT_ALT));
        IO.KeySuper = ImGui::IsKeyDown(GlfwKeyToImGuiKey(GLFW_KEY_LEFT_SUPER)) || ImGui::IsKeyDown(GlfwKeyToImGuiKey(GLFW_KEY_RIGHT_SUPER));
        return false;
    }

    bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& Event)
    {
        ImGuiIO& IO = ImGui::GetIO();
        IO.AddKeyEvent(GlfwKeyToImGuiKey(Event.GetKeyCode()), false);
        IO.KeyCtrl = ImGui::IsKeyDown(GlfwKeyToImGuiKey(GLFW_KEY_LEFT_CONTROL)) || ImGui::IsKeyDown(GlfwKeyToImGuiKey(GLFW_KEY_RIGHT_CONTROL));
        IO.KeyShift = ImGui::IsKeyDown(GlfwKeyToImGuiKey(GLFW_KEY_LEFT_SHIFT)) || ImGui::IsKeyDown(GlfwKeyToImGuiKey(GLFW_KEY_RIGHT_SHIFT));
        IO.KeyAlt = ImGui::IsKeyDown(GlfwKeyToImGuiKey(GLFW_KEY_LEFT_ALT)) || ImGui::IsKeyDown(GlfwKeyToImGuiKey(GLFW_KEY_RIGHT_ALT));
        IO.KeySuper = ImGui::IsKeyDown(GlfwKeyToImGuiKey(GLFW_KEY_LEFT_SUPER)) || ImGui::IsKeyDown(GlfwKeyToImGuiKey(GLFW_KEY_RIGHT_SUPER));
        return false;
    }

    bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& Event)
    {
        ImGuiIO& IO = ImGui::GetIO();
        int KeyCode = Event.GetKeyCode();
        if (KeyCode > 0 && KeyCode < 0x1000)
        {
            IO.AddInputCharacter(KeyCode);
        }
        return false;
    }
}
