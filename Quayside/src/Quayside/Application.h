#pragma once
#include "Core.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"

namespace Quayside
{
	class QUAYSIDE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& Event);
		bool OnWindowClose(WindowCloseEvent& Event);

	private:
		std::unique_ptr<Window> Window;
		bool bRunning = true;
	};

	//to be defined in the CLIENT
	Application* CreateApplication();
}
