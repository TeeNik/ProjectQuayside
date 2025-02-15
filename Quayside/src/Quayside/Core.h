#pragma once

#ifdef QS_PLATFORM_WINDOWS
	#ifdef QS_BUILD_DLL
		#define QUAYSIDE_API __declspec(dllexport)
	#else
		#define QUAYSIDE_API __declspec(dllimport)
	#endif
#else
	#error Quayside only supports Windows!
#endif

#ifdef QS_ENABLE_ASSERTS
	#define QS_ASSERT(x, ...) { if(!(x)) { QS_ERROR("Assetion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define QS_CORE_ASSERT(x, ...) { if(!(x)) { QS_CORE_ERROR("Assetion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define QS_ASSERT(x, ...)
	#define QS_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)