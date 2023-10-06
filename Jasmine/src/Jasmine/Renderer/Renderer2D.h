#pragma once
#include "JM_PCH.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Jasmine/Renderer/OrthographicCamera.h"
#include "Jasmine/Renderer/Texture.h"
#include "Shader.h"
#include "VertexArray.h"

namespace Jasmine {

	struct JM_PSRCTT {
		glm::vec3 pos;
		glm::vec2 size;
		float rotate;
		glm::vec4 color;
		float texIndex;
		float tilingFactor;
	};

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
			if (s_Data.InstanceCount >= JM_Renderer2DData::MaxSquareSize)
				FlushAndReset();

			float texIndex = SoltTexture(texture);
			auto& temp = s_Data.PSRCTT[s_Data.InstanceCount++];
			temp = { position,size,rotation,tintColor,texIndex,tilingFactor };
			s_Data.Stats.DrawCalls++;
		}

		struct Statistics
		{
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;

			uint32_t GetTotalVertexCount() { return QuadCount * 4; }
			uint32_t GetTotalIndexCount() { return QuadCount * 6; }
		};
		
		struct JM_Renderer2DData {
			const static uint32_t MaxSquareSize = 200000;

			JM_PSRCTT PSRCTT[MaxSquareSize];
			uint32_t InstanceCount;

			JM_SP(Shader) TextureShader;
			JM_SP(Texture2D) m_WhiteTex;
			JM_SP(VertexArray) m_SquareVA;
			JM_SP(IndexBuffer) m_SquareIB;
			JM_SP(VertexBuffer) m_JM_SquareVB_PT;
			JM_SP(VertexBuffer) m_JM_SquareVB_PSRCTT;

			Texture2D* TextureSlots[32];
			uint32_t TexSlotIndex;

			Statistics Stats;
		};

		static void ResetStats();
		static Statistics GetStats();

	private:
		static void FlushAndReset();

		inline static JM_Renderer2DData& s_Data = *(new JM_Renderer2DData());

	private:
		inline static uint32_t SoltTexture(Texture2D* texture)
		{
			if (texture == nullptr)
				return 0;

			for (uint32_t i = 0; i < s_Data.TexSlotIndex; i++)
			{
				if (*s_Data.TextureSlots[i] == *texture)
					return i;
			}

			float texIndex = s_Data.TexSlotIndex++;
			s_Data.TextureSlots[(int)texIndex] = texture;
			return texIndex;
		}
	};

}