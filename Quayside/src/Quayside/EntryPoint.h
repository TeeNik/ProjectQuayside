#pragma once

#ifdef QS_PLATFORM_WINDOWS

extern Quayside::Application* Quayside::CreateApplication();

int main(int argc, char** argv)
{
	auto App = Quayside::CreateApplication();
	App->Run();
	delete App;
}

#endif
