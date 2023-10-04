#pragma once

#include "Jasmine.h"
#include <omp.h>

class Particle
{
	glm::vec4 s_color;
	glm::vec4 m_color;
	float m_size;
	glm::vec3 m_position;
	double beginTime;

	float Rotate;
	float maxLiveTime = 3.0f;
	float expansion = 2.0f;

	float destoryfactor = false;

	glm::vec3 m_speed;

	float s_size;
	float r_speed;
	float Gravity;

	glm::mat4 model;
public:
	
	inline bool ShouledDestory() { return destoryfactor < 0.0f; }


	Particle(const glm::vec3& position, float size,const glm::vec4& color,float gravity = 0.0f) :
		m_position(position), s_size(size),m_size(size), m_color(color),s_color(color), beginTime(0),Gravity(gravity) {
		

		static const int Max = RAND_MAX;
		auto rd1 = (double)rand() / (double)Max -0.5f;
		auto rd2 = (double)rand() / (double)Max -0.5f;
		auto rd3 = (double)rand() / (double)Max -0.5f;
		
		Rotate = rd3 * 15.0f + 10.0f;

		m_speed = { rd1,rd2,0.0f };
		m_speed *= size*7.0f;
		
		r_speed = rd3 * 45.0f;
	}

	void OnUpdate(Jasmine::Timestep ts,float Front) {
		if (beginTime == 0)
			beginTime = ts.GetLifeTimeSeconds();

		destoryfactor = 1.0f - (ts.GetLifeTimeSeconds() - beginTime) / maxLiveTime;

		float df1 = pow(destoryfactor, 5.0f);
		float df2 = pow(destoryfactor, 0.2f);
		float df3 = pow(destoryfactor, 7.5f);
		float df4 = pow(destoryfactor, 15.0f);
		

		m_speed.y -= Gravity * ts.GetSeconds() * df1;
		
		Rotate += (r_speed * df1 * ts.GetSeconds());
		m_position += (m_speed * df2 * ts.GetSeconds());
		m_size = df1 * s_size + (1.0f - df1) * s_size * 2;


		m_color = df4 * s_color + (1.0f - df4) * glm::vec4(1.0f,0.25f,0.1f,1.0f);
		m_color = df1 * m_color + (1.0f - df1) * glm::vec4(0.55f);

		m_color.a = df3;

		m_position.z = Front;

		static glm::mat4 nor = glm::mat4(1.0f);
		static glm::mat4 transToCenter = glm::translate(nor, { -0.5f,-0.5f,0.0f });

		model = glm::scale(glm::rotate(glm::translate(nor, m_position), Rotate, { 0.0f,0.0f,1.0f }), { m_size,m_size,1.0f }) * transToCenter;
	}

	void draw() {
		Jasmine::Renderer2D::DrawTransQuad(model, m_color);
	}
};


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

	std::list<Particle> partlist;
	float Front = -10.0f;
	float MaxPartlistSize = 0;

};