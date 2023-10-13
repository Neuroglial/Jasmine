#pragma once
#include "Jasmine.h"

class FlameParticle :public Jasmine::Particle
{
private:
	inline static float p_size = 0.05f;
	inline static glm::vec3 p_color1 = { 1.0f, 0.95f, 0.0f };
	inline static glm::vec3 p_color2 = { 1.0f, 0.25f, 0.1f };
	inline static glm::vec3 p_color3 = glm::vec3(0.45f);

	inline static float p_speed = 1.5f;
	inline static float p_liveTime = 3.0f;
	inline static float p_gravity = -0.25f;
private:
	glm::vec4 color;
	glm::vec3 speed;
	float rotate;
	float rot_speed;
	float lifeTime = 0.0f;

	glm::mat4 model;
public:
	FlameParticle(glm::vec3 position) :Particle(position){
		float SPEED = 5.0f;

		p_liveTime = 3.0f / SPEED;
		p_gravity = SPEED * -0.25f *4.0f;
		p_speed = 1.5f;

		static const int Max = RAND_MAX;
		auto rd1 = (double)rand() / (double)Max - 0.5f;
		auto rd2 = (double)rand() / (double)Max - 0.5f;
		auto rd3 = (double)rand() / (double)Max - 0.5f;

		rotate = rd3 * 180.0f;
		rot_speed = 45.0f * rd3;

		this->position.z += rd3 / 10000.0f;

		speed = { sin(rd1 * 360.0f),cos(rd1 * 360.0f),0.0f };
		speed *= p_size * p_speed * rd2;

		this->position += speed * 1.0f;
	}

	float GetLifeTime() override {
		return lifeTime;
	}

	void OnUpdate(Jasmine::Timestep ts) override {
		lifeTime += ts.GetSeconds();
		float factor = lifeTime / p_liveTime;
		if (factor > 1.0f)
			Destory();

		speed.y -= p_gravity * ts.GetSeconds() * (1.0f - pow(factor,0.25));
		rotate += (rot_speed * ts.GetSeconds());
		position += (speed * ts.GetSeconds());

		auto blend = [](glm::vec3 c1, glm::vec3 c2, float va) {return (1.0f - va) * c1 + c2 * va; };

		glm::vec3 tmp = blend(p_color1, p_color2, pow(factor, 0.5f));
		tmp = blend(tmp, p_color3, pow(factor, 0.75f));
		color = glm::vec4(tmp, 1.0f - pow(factor, 1.5f));

		model = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), rotate, glm::vec3{ 0.0f,0.0f,1.0f }) * glm::scale(glm::mat4(1.0f), glm::vec3(p_size));
	}

	void Draw() override {
		Jasmine::Renderer2D::DrawQuad(model, color);
	}
};


class FlameEmitter :public Jasmine::Emitter
{
public:
	FlameEmitter(glm::vec3& pos = glm::vec3(0.0f), uint32_t MaxCount = 1500) : Emitter(pos, MaxCount) {

	}

	void OnUpdate(Jasmine::Timestep ts) override {

		EitterParticles<FlameParticle>(ts, 200.0f);
		ParticlesUpdate(ts);
	}

	void SetPosition(glm::vec3 pos)
	{
		position = pos;
	}
};