#pragma once

#include "Jasmine/Renderer/RendererAPI.h"

namespace Jasmine {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;
		virtual void Init() override;

		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		inline virtual void DrawIndexed(const JM_SP(VertexArray)& vertexArray, uint32_t indexCount = 0) override { DrawIndexedInstanced(vertexArray, indexCount, 1); }
		virtual void DrawIndexedInstanced(const JM_SP(VertexArray)& vertexArray, uint32_t indexCount = 0,uint32_t instanceCount = 1) override;
		virtual glm::ivec2 GetViewportSize() override;
	};
}
