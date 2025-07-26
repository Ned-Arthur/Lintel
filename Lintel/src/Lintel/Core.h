#pragma once

#ifdef LN_PLATFORM_WINDOWS
	#ifdef LN_BUILD_DLL
		#define LINTEL_API __declspec(dllexport)
	#else
		#define LINTEL_API __declspec(dllimport)
	#endif
#else
	#error Lintel currently only supports Windows
#endif
