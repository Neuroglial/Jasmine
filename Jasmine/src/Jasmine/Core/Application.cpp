#include "JM_PCH.h"

#include "Application.h"
#include "Jasmine/Events/ApplicationEvent.h"
#include "Jasmine/Events/KeyEvent.h"
#include "Jasmine/Core/Log.h"
#include "Jasmine/Renderer/RenderCommand.h"
#include "Jasmine/Renderer/Renderer.h"

#include <GLFW/glfw3.h>

namespace Jasmine {



	Application::Application()
	{
		JM_PROFILE_FUNCTION();

		JM_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(JM_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
		JM_PROFILE_FUNCTION();

		Renderer::Shutdown();
	}

	void Application::Run()
	{
		JM_PROFILE_FUNCTION();

		RenderCommand::SetClearColor({ 0.75f, 0.8f, 0.95f, 1.0f });

		while (m_Running) {
			JM_PROFILE_SCOPE("RunLoop");

			RenderCommand::Clear();

			Timestep timestep = Timestep::UpdateLifeTime(glfwGetTime());

			if (!m_Minimized) {
				for (Layer* layer : m_LayerStack) {
					JM_PROFILE_SCOPE("LayerStack OnUpdate");

					layer->OnUpdate(timestep);
				}

				m_ImGuiLayer->Begin();
				for (Layer* layer : m_LayerStack) {
					JM_PROFILE_SCOPE("LayerStack OnImGuiRender");
					layer->OnImGuiRender();
				}
				m_ImGuiLayer->End();
			}



			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		JM_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(JM_BIND_EVENT_FN(Application::OnWinodwClose));
		dispatcher.Dispatch<WindowResizeEvent>(JM_BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			(*it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		JM_PROFILE_FUNCTION();

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
	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		JM_PROFILE_FUNCTION();

		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}
}
