#include "JM_PCH.h"

#include "Application.h"
#include "Jasmine/Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Jasmine/Log.h"
#include <GLFW/glfw3.h>
#include "Window/WindowsWindow.h"

namespace Jasmine {

#define BIND_EVENT_FN(x) std::bind(&Application::x,this,std::placeholders::_1)

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent, this, std::placeholders::_1));
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
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWinodwClose));

		JM_CORE_INFO(e);
	}

	bool Application::OnWinodwClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}
