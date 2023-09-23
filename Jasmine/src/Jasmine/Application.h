#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "LayerStack.h"
#include "Events/ApplicationEvent.h"
#include "Jasmine/ImGui/ImGuiLayer.h"
#include "Window.h"


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

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;

	private:
		inline static Application* s_Instance = nullptr;
	};

	// To be defined in CLINE
	Application* CreateApplication();
}

