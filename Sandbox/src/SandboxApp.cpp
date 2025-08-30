#include <Quayside.h>

class ExampleLayer : public Quayside::Layer
{
public:
	ExampleLayer() : Layer("ExampleLayer")
	{
	}

	void OnImGuiRender() override
	{
		//ImGui::Begin("Test");
		//ImGui::Text("Test");
		//ImGui::End();
	}
};

class Sandbox : public Quayside::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{
		
	}
};

Quayside::Application* Quayside::CreateApplication()
{
	return new Sandbox();
}