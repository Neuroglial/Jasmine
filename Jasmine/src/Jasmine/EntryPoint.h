#pragma once

#ifdef JM_PLATFORM_WINDOWS

extern Jasmine::Application* Jasmine::CreateApplication();

int main(int argc, char** argv) 
{
	Jasmine::Log::init();
	JM_CORE_WARN("Initialized Log!");
	int a = 5;
	JM_INFO("Hello! Var={0}", a);

	auto app = Jasmine::CreateApplication();
	app->Run();
	delete app;
}

#endif // JASMINE_WINDOWS
