#pragma once

#include "Jasmine/Renderer/RenderCommand.h"
#include "Jasmine/Renderer/OrthographicCamera.h"
#include "Jasmine/Renderer/Shader.h"


namespace Jasmine {

	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();
		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void SetViewportChangeWithWindow(bool enable);
		static glm::ivec2 GetViewportSize();
		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		inline static SceneData* m_SceneData = new SceneData;
		inline static bool ResizeViewportWithWindow = true;
	};


}
