#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	m_CheckerboardTexture = Jasmine::Texture2D::Create("assets/textures/Checkerboard.png");
	m_JM_Logo = Jasmine::Texture2D::Create("assets/textures/Jasmine_Engine_Logo_Light.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Jasmine::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Jasmine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Jasmine::RenderCommand::Clear();

	Jasmine::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Jasmine::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Jasmine::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
	Jasmine::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 2.0f, 2.0f }, m_CheckerboardTexture);
	Jasmine::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.05f }, { 2.0f, 2.0f }, m_JM_Logo);
	Jasmine::Renderer2D::EndScene();

}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::DragFloat2("Square Position", glm::value_ptr(m_Position), 0.001f);
	ImGui::DragFloat2("Square Scale", glm::value_ptr(m_Scale));
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Jasmine::Event& e)
{
	m_CameraController.OnEvent(e);
}