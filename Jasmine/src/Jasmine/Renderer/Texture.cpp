#include "JM_PCH.h"

#include "Texture.h"
#include "Jasmine/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLTexture.h"

namespace Jasmine {

	JM_SP(Texture2D) Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    JM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return JM_CSP(OpenGLTexture2D)(width, height);
		}

		JM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	JM_SP(Texture2D) Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    JM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return JM_CSP(OpenGLTexture2D)(path);
		}

		JM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}