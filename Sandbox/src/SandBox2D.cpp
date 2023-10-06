#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

#include <chrono>
#include <algorithm>
#include <functional>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	JM_PROFILE_FUNCTION();

	m_CheckerboardTexture = Jasmine::Texture2D::Create("assets/textures/Checkerboard.png");
	m_JM_Logo = Jasmine::Texture2D::Create("assets/textures/Jasmine_Engine_Logo_Light.png");

	Jasmine::FramebufferSpecification fbSpec;
	fbSpec.Width = 1280;
	fbSpec.Height = 720;

	ParticleEmitters.emplace_back(new FlameEmitter(glm::vec3{ 1.25f, -0.75f, 0.1f }));
	ParticleEmitters.emplace_back(new FlameEmitter(glm::vec3{ -1.25f, -0.75f, 0.1f }));

	m_Framebuffer = Jasmine::Framebuffer::Create(fbSpec);
}

void Sandbox2D::OnDetach()
{
	JM_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Jasmine::Timestep ts)
{
	JM_PROFILE_FUNCTION();
	
	m_CameraController.OnUpdate(ts);

	for (auto i : ParticleEmitters)
		i->OnUpdate(ts);
	
	//JM_INFO("Count: {0}", ParticleEmitters[0]->GetParticlesCount());

	{
		JM_PROFILE_SCOPE("Renderer Prep");
		//m_Framebuffer->Bind();
		Jasmine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Jasmine::RenderCommand::Clear();
	}

	{
		JM_PROFILE_SCOPE("Renderer Draw");

		static auto tex1 = Jasmine::Texture2D::Create("assets/textures/Quad.png");
		static auto tex2 = Jasmine::Texture2D::Create("assets/textures/Ring.png");
		static auto tex3 = Jasmine::Texture2D::Create("assets/textures/Round.png");

		float Front = -1.0f;
		Jasmine::Renderer2D::BeginScene(m_CameraController.GetCamera());

		Jasmine::Renderer2D::DrawQuad({ -5.0f, -5.0f, Front+=0.0001f }, { 10.0f, 10.0f }, m_CheckerboardTexture, 10.0f);
		Jasmine::Renderer2D::DrawQuad({ -0.7f, -0.7f, Front += 0.0001f }, { 1.4f, 1.4f }, m_JM_Logo, 1.0f);
		Jasmine::Renderer2D::DrawRotatedQuad({ 0.0f ,0.0f,Front += 0.0001f }, { 0.5f,0.5f }, -ts.GetLifeTimeSeconds()*6.0f, tex1, 1.0f, {0.8f,0.5f,0.95f,1.0f});
		Jasmine::Renderer2D::DrawQuad({ -0.15f, -0.15f, Front += 0.0001f }, { 0.3f, 0.3f }, tex3, 1.0f, { 0.95f,0.7f,0.25f,1.0f });
		Jasmine::Renderer2D::DrawQuad({ -0.9f, -0.9f, Front += 0.0001f }, { 1.8f, 1.8f }, tex2, 1.0f, { 0.6f,0.7f,0.95f,1.0f });
		for (auto i : ParticleEmitters)
			i->OnDraw();
		Jasmine::Renderer2D::EndScene();
		//m_Framebuffer->Unbind();
	}
}

void Sandbox2D::OnImGuiRender()
{
	auto viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->WorkPos);
	ImGui::SetNextWindowSize(viewport->WorkSize);


	bool close = true;
	ImGui::Begin("Test", &close, ImGuiWindowFlags_MenuBar|ImGuiWindowFlags_NoTitleBar);

	ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
	ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f),ImGuiDockNodeFlags_AutoHideTabBar);

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit")) Jasmine::Application::Get().Close();
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	ImGui::End();


	ImGui::Begin("Settings");

	auto stats = Jasmine::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	uint32_t textureID = m_CheckerboardTexture->GetRendererID();
	ImGui::Image((void*)textureID, ImVec2{ 256.0f, 256.0f });
	ImGui::End();

	static auto& io = ImGui::GetIO();

	static char FrameTime[128];

	static float ft = io.DeltaTime;
	static float sft = 0.0f;
	static int fc = 0;

	sft += io.DeltaTime;
	fc++;
	if (sft >= 0.05f) {
		ft = sft / fc;
		sft = 0.0f;
		fc = 0;
	}
	
	sprintf_s(FrameTime, 128, "DrawCalls: %5d, Frametime: %5.3f ms", Jasmine::Renderer2D::GetStats().DrawCalls, ft*1000.0f);

	ImGui::Begin("FrameInfo");
	ImGui::Text(FrameTime);
	ImGui::End();
}

void Sandbox2D::OnEvent(Jasmine::Event& e)
{

	Jasmine::EventDispatcher dispathcher(e);
	m_CameraController.OnEvent(e);
	dispathcher.Dispatch< Jasmine::MouseButtonPressedEvent>(JM_BIND_FN(Sandbox2D::OnMousePressed));
}

bool Sandbox2D::OnMousePressed(Jasmine::MouseButtonPressedEvent& e)
{
	return false;
}
