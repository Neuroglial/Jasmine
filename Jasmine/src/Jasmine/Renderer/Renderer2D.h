#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Jasmine/Renderer/OrthographicCamera.h"
#include "Jasmine/Renderer/Texture.h"

namespace Jasmine {

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();
		static void Flush();

		// Primitives
		inline static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
		{
			DrawRotatedQuad({ position.x,position.y,0.0f }, size, 0.0f, nullptr, 1.0f, color);
		}
		inline static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
		{
			DrawRotatedQuad(position, size, 0.0f, nullptr, 1.0f, color);
		}

		inline static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const JM_SP(Texture2D)& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f))
		{
			DrawRotatedQuad({ position.x,position.y,0.0f }, size, 0.0f, texture.get(), tilingFactor, tintColor);
		}

		inline static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const JM_SP(Texture2D)& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f))
		{
			DrawRotatedQuad(position, size, 0.0f, texture.get(), tilingFactor, tintColor);
		}

		inline static void DrawTransQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
		{
			DrawRotatedQuad({ position.x,position.y,0.0f }, size, rotation, nullptr, 1.0f, color);
		}

		inline static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
		{
			DrawRotatedQuad(position, size, rotation, nullptr, 1.0f, color);
		}

		inline static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const JM_SP(Texture2D)& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f))
		{
			DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture.get(), tilingFactor, tintColor);
		}

		inline static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const JM_SP(Texture2D)& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f))
		{
			DrawRotatedQuad(position, size, rotation, texture.get(), tilingFactor, tintColor);
		}

		inline static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, Texture2D* texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f))
		{
			glm::mat4 transform = 
				glm::translate(glm::mat4(1.0f), position) *
				glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f }) *
				glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

			DrawTransQuad(transform, texture, tilingFactor, tintColor);
		}

		inline static void DrawTransQuad(const glm::mat4& model, glm::vec4 color)
		{
			DrawTransQuad(model, nullptr, 1.0f, color);
		}

		static void DrawTransQuad(const glm::mat4& model, Texture2D* texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
	};

}