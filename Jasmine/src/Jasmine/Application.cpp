#include "JM_PCH.h"

#include "Application.h"
#include "Jasmine/Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Jasmine/Log.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Jasmine {



	Application::Application()
	{
		JM_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(JM_BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{

		glClearColor(0.75f, 0.8f, 0.95f, 1.0f);

		while (m_Running) {
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(JM_BIND_EVENT_FN(Application::OnWinodwClose));

		for (auto i = m_LayerStack.end(); i != m_LayerStack.begin();) {
			(*--i)->OnEvent(e);
			if (e.m_Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	bool Application::OnWinodwClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}
