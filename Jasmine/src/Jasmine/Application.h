#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "LayerStack.h"
#include "Events/ApplicationEvent.h"
#include "Jasmine/Renderer/Shader.h"
#include "Jasmine/ImGui/ImGuiLayer.h"
#include "Jasmine/Renderer/VertexArray.h"
#include "Renderer/OrthgraphicCamera.h"
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

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_SquareVA;

		OrthographicCamera m_Camera = OrthographicCamera(-1.6f, 1.6f, -0.9f, 0.9f);

	private:
		inline static Application* s_Instance = nullptr;
	};

	// To be defined in CLINE
	Application* CreateApplication();
}

