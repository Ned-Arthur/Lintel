#include "Log.h"

#include <stdio.h>

namespace Lintel {
	void Log::print(const char* msg)
	{
		printf(msg);
	}
	void Log::println(const char* msg)
	{
		printf("%s\n", msg);
	}
}