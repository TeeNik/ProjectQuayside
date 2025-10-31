#include "qspch.h"
#include "Application.h"
#include "Input.h"
#include "Events/ApplicationEvent.h"
#include "Events/Event.h"
#include "glad/glad.h"

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

		glGenVertexArrays(1, &VertexArray);
		glBindVertexArray(VertexArray);

		glGenBuffers(1, &VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);

		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		glGenBuffers(1, &IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
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
			glClearColor(.1f, .1f, .1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glBindVertexArray(VertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

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

