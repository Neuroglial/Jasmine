#include "JM_PCH.h"
#include "OpenGLRendererAPI.h"


#include <glad/glad.h>

namespace Jasmine {

	void OpenGLRendererAPI::Init()
	{
		JM_PROFILE_FUNCTION();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::DrawIndexedInstanced(const JM_SP(VertexArray)& vertexArray, uint32_t indexCount, uint32_t instanceCount)
	{
		uint32_t count = !indexCount ? vertexArray->GetIndexBuffer()->GetCount() : indexCount;
		//count = 6;
		glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr, instanceCount);
	}

	std::pair<int, int> OpenGLRendererAPI::GetViewportSize()
	{
		int info[4];
		glGetIntegerv(GL_VIEWPORT, info);
		return std::pair<int, int>(info[2], info[3]);
	}

}