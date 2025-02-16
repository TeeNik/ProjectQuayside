#include "qspch.h"
#include "Application.h"

namespace Quayside
{
	Application::Application()
	{
		Window = std::unique_ptr<Quayside::Window>(Window::Create());
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while(bRunning)
		{
			Window->OnUpdate();
		}
	}
}

