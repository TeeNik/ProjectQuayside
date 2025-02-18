#pragma once
#include "Core.h"
#include "LayerStack.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"

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

	private:
		std::unique_ptr<Window> Window;
		bool bRunning = true;

		LayerStack LayerStack;
	};

	//to be defined in the CLIENT
	Application* CreateApplication();
}
