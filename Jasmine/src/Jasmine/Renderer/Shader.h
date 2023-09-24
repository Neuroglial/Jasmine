#pragma once

#include <glm/glm.hpp>

namespace Jasmine {

	class Shader 
	{
	public :
		Shader(const std::string* vsCde, const std::string* fgCde, const std::string* gsCde = NULL);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

	private:
		uint32_t m_RendererID;

	};

}
