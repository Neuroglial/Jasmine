#pragma once

#include "Jasmine/Renderer/Shader.h"
#include <glm/glm.hpp>

// TODO: REMOVE!
typedef unsigned int GLenum;

namespace Jasmine {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const char* filepath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual const std::string& GetName() const override { return m_Name; }

		virtual void SetInt(const std::string& name, int value) override { UploadUniformInt(name, value); }
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) override { UploadUniformFloat3(name, value); }
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) override { UploadUniformFloat4(name, value); }
		virtual void SetMat4(const std::string& name, const glm::mat4& value) override { UploadUniformMat4(name, value); }

		void UploadUniformInt(const std::string& name, int value);
		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

	private:
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

	private:
		uint32_t m_RendererID;
		std::string m_Name;

		void CheckOpenGLShader(uint32_t shaderID);
		void CheckOpenGLProgram(uint32_t programID);
	};

}