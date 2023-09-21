#include "JM_PCH.h"

#include "Application.h"
#include "Jasmine/Events/ApplicationEvent.h"
#include "Jasmine/Log.h"
#include <GLFW/glfw3.h>
#include "Window/WindowsWindow.h"

namespace Jasmine {
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}
	Application::~Application()
	{
	}
	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);

		glClearColor(0.75f, 0.8f, 0.95f, 1.0f);

		while (m_Running) {
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
}
