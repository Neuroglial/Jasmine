#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Jasmine {

	class JASMINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in CLINE
	Application* CreateApplication();
}

