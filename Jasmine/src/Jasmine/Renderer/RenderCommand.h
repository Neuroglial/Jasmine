#pragma once

#include "Jasmine/Renderer/RendererAPI.h"

namespace Jasmine {

	class RenderCommand
	{
	public:

		inline static void Init()
		{
			s_RendererAPI->Init();
		}

		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			s_RendererAPI->SetViewport(x, y, width, height);
		}

		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}

		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		inline static void DrawIndexed(const JM_SP(VertexArray)& vertexArray, uint32_t count = 0)
		{
			s_RendererAPI->DrawIndexed(vertexArray, count);
		}

		inline static void DrawIndexedInstanced(const JM_SP(VertexArray)& vertexArray, uint32_t indexCount = 0, uint32_t instanceCount = 1) 
		{
			s_RendererAPI->DrawIndexedInstanced(vertexArray, indexCount, instanceCount);
		}

		inline static glm::ivec2 GetViewportSize() {
			return s_RendererAPI->GetViewportSize();
		}

	private:
		inline static RendererAPI* s_RendererAPI = RendererAPI::Create();
	};

}