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

				pec.Instance->SetPosition(trans.Position);

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
				auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
				for (auto entity : group)
				{
					auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

					Renderer2D::DrawQuad(transform, sprite.Color);
				}
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
}