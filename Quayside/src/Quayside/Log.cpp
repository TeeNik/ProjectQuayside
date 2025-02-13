#include "qspch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Quayside
{
	std::shared_ptr<logger> Log::CoreLogger;
	std::shared_ptr<logger> Log::ClientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		CoreLogger = spdlog::stdout_color_mt("QUAYSIDE");
		CoreLogger->set_level(spdlog::level::trace);

		ClientLogger = spdlog::stdout_color_mt("APPLICATION");
		ClientLogger->set_level(spdlog::level::trace);
	}

}
