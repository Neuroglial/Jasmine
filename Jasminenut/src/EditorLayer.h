#pragma once

#include <Jasmine.h>
#include "Panels/SceneHierarchyPanel.h"

namespace Jasmine {

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& e) override;
	private:

		// Temp
		JM_SP(VertexArray) m_SquareVA;
		JM_SP(Shader) m_FlatColorShader;
		JM_SP(Framebuffer) m_Framebuffer;

		JM_SP(Texture2D) m_CheckerboardTexture;
		JM_SP(Scene) m_ActiveScene;
		Entity m_SquareEntity;

		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };

		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
		bool m_ViewportFocused = false, m_ViewportHovered = false;

		Entity m_CameraEntity;
		Entity m_SecondCamera;

		bool m_PrimaryCamera = true;

		// Panels
		SceneHierarchyPanel m_SceneHierarchyPanel;
	};

}