#pragma once

#include <glm/glm.hpp>

namespace Jasmine {

	class Shader 
	{
	public :
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const std::string& GetName() const = 0;

		static JM_SP(Shader) Create(const char* filepath);
		static JM_SP(Shader) Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
	};

	class ShaderLibrary
	{
	public:
		void Add(const std::string& name, const JM_SP(Shader)& shader);
		void Add(const JM_SP(Shader)& shader);
		JM_SP(Shader) Load(const char* filepath);
		JM_SP(Shader) Load(const std::string& name, const char* filepath);
		JM_SP(Shader) Load(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);

		bool Exists(const std::string& name) const;

		JM_SP(Shader) Get(const std::string& name);

		template<typename T>
		T* GetCast(const std::string& name) {
			return (T*)Get(name).get();
		}

	private:
		std::unordered_map<std::string, JM_SP(Shader)> m_Shaders;
	};

}
