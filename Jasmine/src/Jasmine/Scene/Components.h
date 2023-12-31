#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Jasmine/Renderer/Camera.h"
#include "SceneCamera.h"
#include "ScriptableEntity.h"
#include "Jasmine/Renderer/Particle.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

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
		glm::vec3 Rotation{ 0.0f };
		glm::vec3 Scale{ 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;

		inline glm::mat4 GetTransform() {
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), Position);
			glm::mat4 rotation = glm::toMat4(glm::quat(glm::radians(Rotation)));
			glm::mat4 scale = glm::scale(glm::mat4(1.0f), Scale);
			return transform * rotation * scale;
		}

		inline operator glm::mat4 () { return GetTransform(); }
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
		TransformComponent transform;

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
