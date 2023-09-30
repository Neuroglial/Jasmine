#pragma once

#ifdef JM_PLATFORM_WINDOWS

extern Jasmine::Application* Jasmine::CreateApplication();

int main(int argc, char** argv) 
{
	Jasmine::Log::init();

	JM_PROFILE_BEGIN_SESSION("Startup", "JasmineProfile-Startup.json");
	auto app = Jasmine::CreateApplication();
	JM_PROFILE_END_SESSION();

	JM_PROFILE_BEGIN_SESSION("Runtime", "JasmineProfile-Runtime.json");
	app->Run();
	JM_PROFILE_END_SESSION();

	JM_PROFILE_BEGIN_SESSION("Startup", "JasmineProfile-Shutdown.json");
	delete app;
	JM_PROFILE_END_SESSION();
}

#endif // JASMINE_WINDOWS
