#include "JM_PCH.h"

#include "WindowsWindow.h"

namespace Jasmine {
	static bool GLFWIsInited = false;

	Window* Window::Create(WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::OnUpdate()
	{
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled != m_Data.VSync) {
			m_Data.VSync = enabled;
			glfwSwapInterval(enabled);
		}
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Height = props.Height;
		m_Data.Width = props.Width;
		m_Data.VSync = false;

		if (!GLFWIsInited) {
			int a = glfwInit();
			JM_CORE_ASSERT(a, "GLFW INIT ERROR!");
		}

		m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height,  m_Data.Title.c_str(), NULL, NULL);

		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

}
