#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "LayerStack.h"
#include "Events/ApplicationEvent.h"
#include "Jasmine/Renderer/Shader.h"
#include "Jasmine/Renderer/VertexArray.h"
#include "Renderer/OrthographicCamera.h"
#include "Window.h"

#include "Jasmine/Core/Timestep.h"
#include "Jasmine/ImGui/ImGuiLayer.h"

namespace Jasmine {

	class JASMINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWinodwClose(WindowCloseEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;
		bool m_Running = true;

		float m_LastFrameTime = 0.0f;

	private:
		inline static Application* s_Instance = nullptr;
	};

	// To be defined in CLINE
	Application* CreateApplication();
}

