#include "JM_PCH.h"
#include "Application.h"

#include "Jasmine/Events/ApplicationEvent.h"
#include "Jasmine/Log.h"

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
			JM_INFO(e);
		}

		if (e.IsInCategory(EventCategoryInput))
		{
			JM_INFO(e);
		}

		while (true);
	}
}
