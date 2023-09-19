#include "Application.h"

#include "Jasmine/Events/ApplicationEvent.h"
#include "Jasmine/Log.h"

#include <iostream>

namespace Jasmine {
	Application::Application()
	{
	}
	Application::~Application()
	{
	}
	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);

		if (e.IsInCategory(EventCategoryApplication))
		{
			std::cout << e << std::endl;
		}

		if (e.IsInCategory(EventCategoryInput))
		{
			JM_TRACE(e);
		}

		while (true)
		{
		}
	}
}
