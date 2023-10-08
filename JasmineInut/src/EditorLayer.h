#pragma once

#include <Jasmine.h>

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
		Jasmine::OrthographicCameraController m_CameraController;

		// Temp
		JM_SP(VertexArray) m_SquareVA;
		JM_SP(Shader) m_FlatColorShader;
		JM_SP(Framebuffer) m_Framebuffer;

		JM_SP(Texture2D) m_CheckerboardTexture;

		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };

		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	};

}