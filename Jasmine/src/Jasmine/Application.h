#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window/Window.h"


namespace Jasmine {

	class JASMINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// To be defined in CLINE
	Application* CreateApplication();
}

