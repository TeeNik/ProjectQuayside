#pragma once

#ifdef QS_PLATFORM_WINDOWS

extern Quayside::Application* Quayside::CreateApplication();

int main(int argc, char** argv)
{
	Quayside::Log::Init();
	QS_CORE_WARN("Init Log");

	int x = 15;
	QS_INFO("X = {0}", x);

	auto App = Quayside::CreateApplication();
	App->Run();
	delete App;
}

#endif
