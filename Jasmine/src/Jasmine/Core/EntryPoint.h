#pragma once

#ifdef JM_PLATFORM_WINDOWS

extern Jasmine::Application* Jasmine::CreateApplication();

int main(int argc, char** argv) 
{
	Jasmine::Log::init();

	auto app = Jasmine::CreateApplication();
	app->Run();
	delete app;
}

#endif // JASMINE_WINDOWS
