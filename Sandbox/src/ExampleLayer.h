#pragma once

#include "Jasmine.h"

class ExampleLayer : public Jasmine::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Jasmine::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Jasmine::Event& e) override;
private:
	Jasmine::ShaderLibrary m_ShaderLibrary;
	JM_SP(Jasmine::Shader) m_Shader;
	JM_SP(Jasmine::VertexArray) m_VertexArray;

	JM_SP(Jasmine::Shader) m_FlatColorShader;
	JM_SP(Jasmine::VertexArray) m_SquareVA;

	JM_SP(Jasmine::Texture) m_Texture, m_ChernoLogoTexture;

	Jasmine::OrthographicCameraController m_CameraController;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};