#pragma once

#include "Jasmine.h"

class Sandbox2D : public Jasmine::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Jasmine::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Jasmine::Event& e) override;
private:
	Jasmine::OrthographicCameraController m_CameraController;

	// Temp
	JM_SP(Jasmine::VertexArray) m_SquareVA;
	JM_SP(Jasmine::Shader) m_FlatColorShader;

	glm::vec2 m_Position = { 0.0f,0.0f };
	glm::vec2 m_Scale = { 1.0f,1.0f };
	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};