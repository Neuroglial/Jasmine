#pragma once

#include "entt.hpp"


#include "Jasmine/Core/Timestep.h"

namespace Jasmine {

	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = "Entity");
		void OnUpdate(Timestep ts);
	private:
		entt::registry m_Registry;
		friend class Entity;
	};

}