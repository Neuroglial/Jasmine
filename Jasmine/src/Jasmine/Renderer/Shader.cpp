#include "JM_PCH.h"

#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

#include "Jasmine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Jasmine {

	JM_SP(Shader) Shader::Create(const char* filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    JM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return JM_SP(OpenGLShader)(new OpenGLShader(filepath));
		}

		JM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}


	JM_SP(Shader) Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: JM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL: return JM_SP(OpenGLShader)(new OpenGLShader(name, vertexSrc, fragmentSrc));
		}
		JM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	void ShaderLibrary::Add(const std::string& name, const JM_SP(Shader)& shader)
	{
		JM_CORE_ASSERT(!Exists(name), "Shader already exists!");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const JM_SP(Shader)& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	JM_SP(Shader) ShaderLibrary::Load(const char* filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	JM_SP(Shader) ShaderLibrary::Load(const std::string& name, const char* filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	JM_SP(Shader) ShaderLibrary::Load(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		auto shader = Shader::Create(name, vertexSrc, fragmentSrc);
		Add(shader);
		return shader;
	}

	JM_SP(Shader) ShaderLibrary::Get(const std::string& name)
	{
		JM_CORE_ASSERT(Exists(name), "Shader not found!");
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}


}