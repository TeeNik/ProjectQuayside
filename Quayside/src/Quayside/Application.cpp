#include "qspch.h"
#include "Application.h"
#include <GL/gl.h>
#include "Events/ApplicationEvent.h"
#include "Events/Event.h"

namespace Quayside
{
//#define BIND_EVENT_FUNC(x) std::bind(&x, this, std::placeholders::_1)
#define BIND_EVENT_FUNC(x) [this](auto&& PH1) {return x(std::forward<decltype(PH1)>(PH1));}
	
	Application::Application()
	{
		Window = std::unique_ptr<Quayside::Window>(Window::Create());
		Window->SetEventCallback(BIND_EVENT_FUNC(Application::OnEvent));
	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* Layer)
	{
		LayerStack.PushLayer(Layer);
	}

	void Application::PushOverlay(Layer* Layer)
	{
		LayerStack.PushOverlay(Layer);
	}

	void Application::Run()
	{
		while(bRunning)
		{
			glClearColor(50/255.0f, 74/255.f, 158/255.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			for (auto* Layer : LayerStack)
			{
				Layer->OnUpdate();
			}
			
			Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& Event)
	{
		EventDispatcher Dispatcher(Event);
		Dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(Application::OnWindowClose));
		QS_CORE_TRACE(Event.ToString());

		for (auto it = LayerStack.end(); it != LayerStack.begin();)
		{
			(*--it)->OnEvent(Event);
			if (Event.bHandled)
			{
				break;
			}
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& Event)
	{
		bRunning = false;
		return true;
	}
}

