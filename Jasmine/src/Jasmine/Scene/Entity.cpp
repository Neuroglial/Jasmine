#include "JM_PCH.h"
#include "Entity.h"

namespace Jasmine {

	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{
	}

}