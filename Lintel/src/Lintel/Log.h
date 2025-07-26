#pragma once

#include "Core.h"

namespace Lintel {

	class LINTEL_API Log
	{
	public:
		static void print(const char* msg);
		static void println(const char* msg);
	};

}
