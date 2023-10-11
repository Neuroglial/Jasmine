#pragma once

#include "Jasmine/Core/Base.h"
#include "Scene.h"

namespace Jasmine {

	class SceneSerializer
	{
	public:
		SceneSerializer(const JM_SP(Scene)& scene);

		void Serialize(const std::string& filepath);
		void SerializeRuntime(const std::string& filepath);

		bool Deserialize(const std::string& filepath);
		bool DeserializeRuntime(const std::string& filepath);
	private:
		JM_SP(Scene) m_Scene;
	};

}