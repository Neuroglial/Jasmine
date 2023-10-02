#include "JM_PCH.h"

#include "Buffer.h"
#include "Jasmine/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Jasmine {

	JM_SP(VertexBuffer) VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    JM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return JM_CSP(OpenGLVertexBuffer)(size);
		}

		JM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	JM_SP(VertexBuffer) VertexBuffer::Create(float* vertices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    JM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return JM_CSP(OpenGLVertexBuffer)(vertices, count);
		}

		JM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	JM_SP(IndexBuffer) IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    JM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return JM_CSP(OpenGLIndexBuffer)(indices, size);
		}

		JM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}