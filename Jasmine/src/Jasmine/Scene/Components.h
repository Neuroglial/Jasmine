#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Jasmine/Renderer/Camera.h"
#include "SceneCamera.h"
#include "ScriptableEntity.h"
#include "Jasmine/Renderer/Particle.h"

namespace Jasmine {

	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: Tag(tag) {}
	};

	struct TransformComponent
	{
		glm::vec3 Position{ 0.0f };
		glm::vec3 Rotate{ 0.0f };
		glm::vec3 Scale{ 1.0f };
		glm::mat4 Transform{ 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& transform)
			: Transform(transform) {}

		void FlushTransform() {
			Transform = glm::translate(glm::mat4(1.0f), Position);
			Transform = glm::rotate(Transform, glm::radians(Rotate.y), {0.0f,1.0f,0.0f});
			Transform = glm::rotate(Transform, glm::radians(Rotate.x), { 1.0f,0.0f,0.0f });
			Transform = glm::rotate(Transform, glm::radians(Rotate.z), { 0.0f,0.0f,1.0f });
			Transform = glm::scale(Transform, Scale);

		}

		operator glm::mat4& () { return Transform; }
		operator const glm::mat4& () const { return Transform; }
	};

	struct SpriteRendererComponent
	{
		glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color)
			: Color(color) {}
	};

	struct CameraComponent
	{
		SceneCamera Camera;
		bool Primary = true; // TODO: think about moving to Scene
		bool FixedAspectRatio = false;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};

	struct NativeScriptComponent
	{
		ScriptableEntity* Instance = nullptr;

		ScriptableEntity* (*InstantiateScript)();
		void (*DestroyScript)(NativeScriptComponent*);

		template<typename T>
		void Bind()
		{
			InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
			DestroyScript = [](NativeScriptComponent* nsc) { delete nsc->Instance; nsc->Instance = nullptr; };
		}
	};

	struct ParticleEmitterComponent
	{
		Emitter* Instance = nullptr;

		Emitter* (*InstaniateEmitter)(glm::vec3&);
		void (*DestroyEmitter)(ParticleEmitterComponent*);

		ParticleEmitterComponent() = default;

		template<typename T>
		void Bind()
		{
			InstaniateEmitter = [](glm::vec3& position) { return static_cast<Emitter*>(new T(position)); };
			DestroyEmitter = [](ParticleEmitterComponent* pec) {delete pec->Instance; pec->Instance = nullptr; };
		}
	};
}
