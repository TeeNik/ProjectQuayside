#include "qspch.h"
#include "Application.h"
#include <GL/gl.h>
#include "Input.h"
#include "Events/ApplicationEvent.h"
#include "Events/Event.h"

namespace Quayside
{
	Application* Application::Instance = nullptr;
	
	Application::Application()
	{
		QS_CORE_ASSERT(!Instance, "Application already exists");
		Application::Instance = this;
		
		Window = std::unique_ptr<Quayside::Window>(Window::Create());
		Window->SetEventCallback(BIND_EVENT_FUNC(Application::OnEvent));

		ImGuiLayer = new Quayside::ImGuiLayer();
		PushOverlay(ImGuiLayer);
	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* Layer)
	{
		LayerStack.PushLayer(Layer);
		Layer->OnAttach();
	}

	void Application::PushOverlay(Layer* Layer)
	{
		LayerStack.PushOverlay(Layer);
		Layer->OnAttach();
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

			ImGuiLayer->Begin();
			for (auto* Layer : LayerStack)
			{
				Layer->OnImGuiRender();
			}
			ImGuiLayer->End();

			Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& Event)
	{
		EventDispatcher Dispatcher(Event);
		Dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(Application::OnWindowClose));

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

