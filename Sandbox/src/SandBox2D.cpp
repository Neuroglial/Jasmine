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
}

void Sandbox2D::OnDetach()
{
	JM_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Jasmine::Timestep ts)
{
	for (auto i = partlist.begin(); i != partlist.end(); i = partlist.begin()) {
		if (i->ShouledDestory()) 
			partlist.erase(i);
		else break;
	}

	
		static std::vector<std::function<void()>> upds;
	{
		JM_PROFILE_SCOPE("Partlist Update1");
		if (upds.size() < partlist.size())
			upds.resize(partlist.size() + 200);
		int j = 0;
		for (auto i = partlist.begin(); i != partlist.end(); i++, j++) {
			upds[j] = std::bind(&Particle::OnUpdate, &*i, ts,Front+=0.0001f);
		}
	}
		
	{
		JM_PROFILE_SCOPE("Partlist Update2");
		omp_set_num_threads(8);
#pragma omp parallel for
		for (int i = 0; i < partlist.size(); i++) {
			upds[i]();
		}
	}



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


		Front = -1.0f;
		Jasmine::Renderer2D::BeginScene(m_CameraController.GetCamera());

		Jasmine::Renderer2D::DrawQuad({ -5.0f, -5.0f, Front+=0.0001f }, { 10.0f, 10.0f }, m_CheckerboardTexture, 10.0f);
		Jasmine::Renderer2D::DrawQuad({ -0.7f, -0.7f, Front += 0.0001f }, { 1.4f, 1.4f }, m_JM_Logo, 1.0f);
		Jasmine::Renderer2D::DrawRotatedQuad({ 0.0f ,0.0f,Front += 0.0001f }, { 0.5f,0.5f }, -ts.GetLifeTimeSeconds()/15.0f, tex1, 1.0f, {0.8f,0.5f,0.95f,1.0f});
		Jasmine::Renderer2D::DrawQuad({ -0.15f, -0.15f, Front += 0.0001f }, { 0.3f, 0.3f }, tex3, 1.0f, { 0.95f,0.7f,0.25f,1.0f });
		Jasmine::Renderer2D::DrawQuad({ -0.9f, -0.9f, Front += 0.0001f }, { 1.8f, 1.8f }, tex2, 1.0f, { 0.6f,0.7f,0.95f,1.0f });
		auto mp = Jasmine::Input::GetMousePosition();
		glm::vec2 pos = m_CameraController.GetCamera().GetMousePos({ mp.first,mp.second });
		Jasmine::Renderer2D::DrawQuad({pos.x-0.05f,pos.y-0.05f,Front += 0.0001f }, { 0.1f,0.1f }, { 1.0f,0.5f,0.4f,1.0f });
		for (auto& i : partlist)
			i.draw();
		Jasmine::Renderer2D::EndScene();

		static glm::vec2 lastpos;
		static float OurFront = Front;
		float count = ts.GetSeconds() * MaxPartlistSize / 3.0f;
		for (float i = 0; i <count ; i++) {

			float factor = i / count;
			glm::vec2 tpos = lastpos * (1.0f - factor) + pos * factor;

			partlist.emplace_back(Particle({ tpos.x,tpos.y,0.0f }, 0.05f, m_SquareColor,0.25f));
		}
		lastpos = pos;
	}
}

void Sandbox2D::OnImGuiRender()
{
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

		if (ft < 16.0f / 1000.0f)
			MaxPartlistSize += 50.0f;
		else
			MaxPartlistSize -= 5.0f;
	}

	sprintf(FrameTime, "ParticleCount: %6d Frametime: %5.3f ms",(int)partlist.size(), ft*1000.0f);

	 
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
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
