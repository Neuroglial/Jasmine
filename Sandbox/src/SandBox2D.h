#pragma once

#include "Jasmine.h"
#include <omp.h>
#include <map>
#include <unordered_map>
#include <type_traits>
#include "../assets/particle/FlameEmitter.h"

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
	bool OnMousePressed(Jasmine::MouseButtonPressedEvent& e);
private:
	Jasmine::OrthographicCameraController m_CameraController;

	// Temp
	JM_SP(Jasmine::VertexArray) m_SquareVA;
	JM_SP(Jasmine::Shader) m_FlatColorShader;
	JM_SP(Jasmine::Texture2D) m_CheckerboardTexture;
	JM_SP(Jasmine::Texture2D) m_JM_Logo;

	glm::vec2 m_Position = { 0.0f,0.0f };
	glm::vec2 m_Scale = { 1.0f,1.0f };
	glm::vec4 m_SquareColor = { 1.0f, 0.95f, 0.0f, 1.0f };

	std::vector<Jasmine::Emitter*> ParticleEmitters;
};