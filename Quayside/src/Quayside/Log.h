#pragma once
#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Quayside
{
	using spdlog::logger;

	class QUAYSIDE_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<logger>& GetCoreLogger() { return CoreLogger; }
		inline static std::shared_ptr<logger>& GetClientLogger() { return ClientLogger; }

	private:
		static std::shared_ptr<logger> CoreLogger;
		static std::shared_ptr<logger> ClientLogger;
	};
}

//core log macros
#define QS_CORE_TRACE(...)  ::Quayside::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define QS_CORE_ERROR(...)  ::Quayside::Log::GetCoreLogger()->error(__VA_ARGS__)
#define QS_CORE_WARN(...)   ::Quayside::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define QS_CORE_INFO(...)   ::Quayside::Log::GetCoreLogger()->info(__VA_ARGS__)
#define QS_CORE_FATAL(...)  ::Quayside::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//client log macros
#define QS_TRACE(...)  ::Quayside::Log::GetClientLogger()->trace(__VA_ARGS__)
#define QS_ERROR(...)  ::Quayside::Log::GetClientLogger()->error(__VA_ARGS__)
#define QS_WARN(...)   ::Quayside::Log::GetClientLogger()->warn(__VA_ARGS__)
#define QS_INFO(...)   ::Quayside::Log::GetClientLogger()->info(__VA_ARGS__)
#define QS_FATAL(...)  ::Quayside::Log::GetClientLogger()->fatal(__VA_ARGS__)