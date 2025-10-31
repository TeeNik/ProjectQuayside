#pragma once
#include "Core.h"
#include "LayerStack.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "ImGui/ImGuiLayer.h"

namespace Quayside
{
	class QUAYSIDE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void PushLayer(Layer* Layer);
		void PushOverlay(Layer* Layer);


		void Run();
		void OnEvent(Event& Event);
		bool OnWindowClose(WindowCloseEvent& Event);

		inline Window& GetWindow() { return *Window; }
		inline static Application& Get() { return *Instance; }

	private:
		std::unique_ptr<Window> Window;
		ImGuiLayer* ImGuiLayer;
		bool bRunning = true;
		LayerStack LayerStack;

		unsigned int VertexArray, VertexBuffer, IndexBuffer;

		static Application* Instance;
	};

	//to be defined in the CLIENT
	Application* CreateApplication();
}
