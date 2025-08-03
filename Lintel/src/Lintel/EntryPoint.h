#pragma once

#ifdef LN_PLATFORM_WINDOWS

extern Lintel::Application* Lintel::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Lintel::CreateApplication();
	app->Run();
	delete app;
}

#endif