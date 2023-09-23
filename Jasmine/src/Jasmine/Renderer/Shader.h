#pragma once

namespace Jasmine {

	class Shader 
	{
	public :
		Shader(const std::string* vsCde, const std::string* fgCde, const std::string* gsCde = NULL);
		~Shader();

		void Bind() const;
		void Unbind() const;

	private:
		uint32_t m_RendererID;

	};

}
