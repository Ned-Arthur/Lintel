#pragma once

#ifdef LN_PLATFORM_WINDOWS


int main(int argc, char** argv)
{
	auto app = Lintel::CreateApplication();
	app->Run();
	delete app;
}

#endif