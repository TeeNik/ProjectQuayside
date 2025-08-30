#pragma once

#ifdef QS_PLATFORM_WINDOWS
#if QS_DYNAMIC_LINK
	#ifdef QS_BUILD_DLL
		#define QUAYSIDE_API __declspec(dllexport)
	#else
		#define QUAYSIDE_API __declspec(dllimport)
	#endif
#else
	#define QUAYSIDE_API
#endif
#else
	#error Quayside only supports Windows!
#endif

#ifdef QS_DEBUG
	#define QS_ENABLE_ASSERTS
#endif

#ifdef QS_ENABLE_ASSERTS
	#define QS_ASSERT(x, ...) { if(!(x)) { QS_ERROR("Assetion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define QS_CORE_ASSERT(x, ...) { if(!(x)) { QS_CORE_ERROR("Assetion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define QS_ASSERT(x, ...)
	#define QS_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

//#define BIND_EVENT_FUNC(x) std::bind(&x, this, std::placeholders::_1)
#define BIND_EVENT_FUNC(func) [this](auto&& PH1) {return func(std::forward<decltype(PH1)>(PH1));}