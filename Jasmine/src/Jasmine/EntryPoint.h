#pragma once

#ifdef JASMINE_WINDOWS

extern Jasmine::Application* Jasmine::CreateApplication();

int main(int argc, char** argv) 
{
	auto app = Jasmine::CreateApplication();
	app->Run();
	delete app;
}

#endif // JASMINE_WINDOWS
