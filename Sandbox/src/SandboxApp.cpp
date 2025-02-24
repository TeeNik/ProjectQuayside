#include <Quayside.h>

class ExampleLayer : public Quayside::Layer
{
public:
	ExampleLayer() : Layer("ExampleLayer")
	{
	}

	void OnUpdate() override
	{
		//QS_INFO("ExampleLayer::OnUpdate");
	}

	void OnEvent(Quayside::Event& Event) override
	{
		//QS_WARN("ExampleLayer::OnEvent {0}", Event.ToString());
	}
};

class Sandbox : public Quayside::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Quayside::ImGuiLayer);
	}

	~Sandbox()
	{
		
	}
};

Quayside::Application* Quayside::CreateApplication()
{
	return new Sandbox();
}