#pragma once
#include "Core.h"
#include "Window.h"

namespace Quayside
{
	class QUAYSIDE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	private:
		std::unique_ptr<Window> Window;
		bool bRunning = true;
	};

	//to be defined in the CLIENT
	Application* CreateApplication();
}
