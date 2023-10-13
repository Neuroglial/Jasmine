#pragma once

#include "Jasmine/Core/Base.h"
#include "Jasmine/Core/Log.h"
#include "Jasmine/Scene/Scene.h"
#include "Jasmine/Scene/Entity.h"

namespace Jasmine {

	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const JM_SP(Scene)& scene);

		void SetContext(const JM_SP(Scene)& scene);

		void OnImGuiRender();

		Entity GetSelectedEntity() const { return m_SelectionContext; }
	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);
	private:
		JM_SP(Scene) m_Context;
		Entity m_SelectionContext;
	};

}