#include "JM_PCH.h"
#include "Framebuffer.h"

#include "Jasmine/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Jasmine {

	JM_SP(Framebuffer) Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    JM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return JM_CSP(OpenGLFramebuffer)(spec);
		}

		JM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
