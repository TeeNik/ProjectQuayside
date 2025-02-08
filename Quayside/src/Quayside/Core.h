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

#define BIT(x) (1 << x)