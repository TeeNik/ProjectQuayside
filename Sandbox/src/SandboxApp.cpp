#include <Quayside.h>

class Sandbox : public Quayside::Application
{
public:
	Sandbox()
	{
		
	}

	~Sandbox()
	{
		
	}
};

Quayside::Application* Quayside::CreateApplication()
{
	return new Sandbox();
}