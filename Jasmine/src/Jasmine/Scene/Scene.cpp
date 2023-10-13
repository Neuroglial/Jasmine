#include "JM_PCH.h"

#include "Scene.h"


#include "Entity.h"

#include "Components.h"
#include "Jasmine/Renderer/Renderer2D.h"

#include <glm/glm.hpp>

namespace Jasmine {

	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
	}

	void Scene::DestroyEntity(Entity entity)
	{
		m_Registry.destroy(entity.GetEnity());
	}


	Entity Scene::CreateEntity(const std::string& name)
	{

		Entity entity = {m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		entity.AddComponent<TagComponent>(name);

		return entity;
	}

	void Scene::OnUpdate(Timestep ts)
	{
		// Update scripts
		{
			m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
				{
					if (!nsc.Instance)
					{
						nsc.Instance = nsc.InstantiateScript();
						nsc.Instance->m_Entity = Entity{ entity, this };
						nsc.Instance->OnCreate();
					}

					nsc.Instance->OnUpdate(ts);
				});
		}

		//Update Emitter
		{
			auto view = m_Registry.view<TransformComponent, ParticleEmitterComponent>();
			for (auto entity : view) {
				auto [trans, pec] = view.get<TransformComponent, ParticleEmitterComponent>(entity);

				if (!pec.Instance) 
				{
					pec.Instance = pec.InstaniateEmitter(trans.Position);
				}

				pec.Instance->SetPosition(trans.Position + pec.transform.Position*trans.Scale);

				pec.Instance->OnUpdate(ts);

			}
		}

		// Render 2D
		Camera* mainCamera = nullptr;
		glm::mat4* cameraTransform = nullptr;
		{
			auto view = m_Registry.view<TransformComponent, CameraComponent>();
			for (auto entity : view)
			{
				auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

				if (camera.Primary)
				{
					mainCamera = &camera.Camera;
					cameraTransform = &transform.GetTransform();
					break;
				}
			}
		}

		if (mainCamera)
		{
			Renderer2D::BeginScene(mainCamera->GetProjection(), *cameraTransform);

			//Draw Quad
			{

				auto view = m_Registry.view<TransformComponent, SpriteRendererComponent>();
				for (auto entity : view) {
					auto [transform, sprite] = view.get<TransformComponent, SpriteRendererComponent>(entity);

					Renderer2D::DrawQuad(transform.GetTransform(), sprite.Color);
				}
				//auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
				//for (auto entity : group)
				//{
				//	auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
				//
				//	Renderer2D::DrawQuad(transform, sprite.Color);
				//}
			}

			//Draw Particles
			{
				m_Registry.view<ParticleEmitterComponent>().each([=](auto entity, auto& pec)
					{
						if (pec.Instance)
							pec.Instance->OnDraw();
					}
				);
			}

			Renderer2D::EndScene();
		}
	}
	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;

		// Resize our non-FixedAspectRatio cameras
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& cameraComponent = view.get<CameraComponent>(entity);
			if (!cameraComponent.FixedAspectRatio)
				cameraComponent.Camera.SetViewportSize(width, height);
		}
	}

	Entity Scene::GetPrimaryCameraEntity()
	{
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			const auto& camera = view.get<CameraComponent>(entity);
			if (camera.Primary)
				return Entity{ entity, this };
		}
		return {};
	}

	template<typename T>
	void Scene::OnComponentAdded(Entity entity, T& component)
	{
		static_assert(false);
	}

	template<>
	void Scene::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<CameraComponent>(Entity entity, CameraComponent& component)
	{
		component.Camera.SetViewportSize(m_ViewportWidth, m_ViewportHeight);
	}

	template<>
	void Scene::OnComponentAdded<SpriteRendererComponent>(Entity entity, SpriteRendererComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<TagComponent>(Entity entity, TagComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<NativeScriptComponent>(Entity entity, NativeScriptComponent& component)
	{
	}
}