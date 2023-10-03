#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

#include <chrono>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	JM_PROFILE_FUNCTION();

	m_CheckerboardTexture = Jasmine::Texture2D::Create("assets/textures/Checkerboard.png");
	m_JM_Logo = Jasmine::Texture2D::Create("assets/textures/Jasmine_Engine_Logo_Light.png");
}

void Sandbox2D::OnDetach()
{
	JM_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Jasmine::Timestep ts)
{
	JM_PROFILE_FUNCTION();
	m_CameraController.OnUpdate(ts);

	{
		JM_PROFILE_SCOPE("Renderer Prep");
		Jasmine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Jasmine::RenderCommand::Clear();
	}

	{
		static auto tex1 = Jasmine::Texture2D::Create("assets/textures/Quad.png");
		static auto tex2 = Jasmine::Texture2D::Create("assets/textures/Ring.png");
		static auto tex3 = Jasmine::Texture2D::Create("assets/textures/Round.png");
		

		JM_PROFILE_SCOPE("Renderer Draw");
		Jasmine::Renderer2D::BeginScene(m_CameraController.GetCamera());

		Jasmine::Renderer2D::DrawQuad({ -5.0f, -5.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture, 10.0f);
		Jasmine::Renderer2D::DrawQuad({ -5.0f, -5.0f, -0.05f }, { 10.0f, 10.0f }, m_JM_Logo, 7.0f);
		Jasmine::Renderer2D::DrawRotatedQuad({ 0.0f ,0.0f,0.1f }, { 0.5f,0.5f }, -ts.GetLifeTimeSeconds()/15.0f, tex1, 1.0f, {0.8f,0.5f,0.95f,1.0f});
		Jasmine::Renderer2D::DrawQuad({ -0.15f, -0.15f, 0.15f }, { 0.3f, 0.3f }, tex3, 1.0f, { 0.95f,0.7f,0.25f,1.0f });
		Jasmine::Renderer2D::DrawQuad({ -0.9f, -0.9f, 0.2f }, { 1.8f, 1.8f }, tex2, 1.0f, { 0.6f,0.7f,0.95f,1.0f });

		Jasmine::Renderer2D::EndScene();

	}
}

void Sandbox2D::OnImGuiRender()
{
	static auto& io = ImGui::GetIO();
	static char FramerateString[128];
	sprintf(FramerateString, "Framerate: %5.2f", io.Framerate);

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::Text(FramerateString);
	ImGui::End();
}

void Sandbox2D::OnEvent(Jasmine::Event& e)
{
	m_CameraController.OnEvent(e);
}