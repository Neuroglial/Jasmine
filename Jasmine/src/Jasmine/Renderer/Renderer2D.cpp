#include "JM_PCH.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Jasmine {

	struct JM_Vertex2D
	{
		glm::vec3 Position;
		glm::vec2 TexCoord;
	};

	struct JM_SquareVB {
		JM_Vertex2D v0{ { 0.0f, 0.0f, 0.0f}, { 0.0f, 0.0f} };
		JM_Vertex2D v1{ { 1.0f, 0.0f, 0.0f}, { 1.0f, 0.0f} };
		JM_Vertex2D v2{ { 1.0f, 1.0f, 0.0f}, { 1.0f, 1.0f} };
		JM_Vertex2D v3{ { 0.0f, 1.0f, 0.0f}, { 0.0f, 1.0f} };
	};

	struct JM_SquareEB
	{
		uint32_t e1 = 0;
		uint32_t e2 = 1;
		uint32_t e3 = 2;

		uint32_t e4 = 0;
		uint32_t e5 = 2;
		uint32_t e6 = 3;
	};

	struct JM_CTTM {
		glm::vec4 color;
		float texIndex;
		float tiling;
		glm::mat4 model;
	};

	struct JM_Renderer2DDate {
		const static uint32_t MaxSquareSize = 1000000;
		const uint32_t MaxCTTMSize = MaxSquareSize * (4 + 1 + 1 + 16);

		JM_CTTM CTTM[MaxSquareSize];

		uint32_t InstanceCount;

		JM_SP(Shader) TextureShader;
		JM_SP(Texture2D) m_WhiteTex;
		JM_SP(VertexArray) m_SquareVA;
		JM_SP(IndexBuffer) m_SquareIB;
		JM_SP(VertexBuffer) m_JM_SquareVB_Pos_TexC;
		JM_SP(VertexBuffer) m_JM_SquareVB_Color_TexInd_Tile_Model;

		Texture2D* TextureSlots[32];
		uint32_t TexSlotIndex;
	};

	static JM_Renderer2DDate& s_Date = *(new JM_Renderer2DDate());

	void Renderer2D::Init()
	{
		JM_PROFILE_FUNCTION();

		// Create the White Texture;
		s_Date.m_WhiteTex = Texture2D::Create(1, 1);
		uint32_t w_data = 0xffffffff;
		s_Date.m_WhiteTex->SetData(&w_data, sizeof(uint32_t));
		s_Date.TextureSlots[0] = s_Date.m_WhiteTex.get();

		// Create VertexArray
		s_Date.m_SquareVA = VertexArray::Create();
		float svb[] = {
			 0.0f, 0.0f, 0.0f ,   0.0f, 0.0f ,
			 1.0f, 0.0f, 0.0f ,   1.0f, 0.0f ,
			 1.0f, 1.0f, 0.0f ,   1.0f, 1.0f ,
			 0.0f, 1.0f, 0.0f ,   0.0f, 1.0f
		};

		s_Date.m_JM_SquareVB_Pos_TexC = VertexBuffer::Create(svb, sizeof(svb));
		s_Date.m_JM_SquareVB_Pos_TexC->SetLayout(
			{ {ShaderDataType::Float3, "a_Position;"},
			  {ShaderDataType::Float2, "a_TexCoord;"} });
		
		s_Date.m_JM_SquareVB_Color_TexInd_Tile_Model = VertexBuffer::Create(s_Date.MaxCTTMSize);
		s_Date.m_JM_SquareVB_Color_TexInd_Tile_Model->SetLayout(
			{ {ShaderDataType::Float4, "a_Color"},
			  {ShaderDataType::Float,	   "a_TexIndex"},
			  {ShaderDataType::Float,  "a_TilingFactor"},
			  {ShaderDataType::Float4, "a_M1"},
			  {ShaderDataType::Float4, "a_M2"} ,
			  {ShaderDataType::Float4, "a_M3"} ,
			  {ShaderDataType::Float4, "a_M4"} });
		s_Date.m_JM_SquareVB_Color_TexInd_Tile_Model->SetAtrribDivisorFactor(1);
		
		uint32_t seb[] = {
			0,1,2, 0,2,3
		};

		s_Date.m_SquareIB = IndexBuffer::Create(seb, sizeof(seb) / sizeof(uint32_t));
		s_Date.m_SquareVA->AddVertexBuffer(s_Date.m_JM_SquareVB_Pos_TexC);
		s_Date.m_SquareVA->AddVertexBuffer(s_Date.m_JM_SquareVB_Color_TexInd_Tile_Model);
		s_Date.m_SquareVA->SetIndexBuffer(s_Date.m_SquareIB);

		s_Date.TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		
		int texs[32];
		for (int i = 0; i < 32; i++)
			texs[i] = i;
		s_Date.TextureShader->Bind();
		s_Date.TextureShader->SetIntArray("u_Textures", texs, 32);

	}

	void Renderer2D::Shutdown()
	{
		JM_PROFILE_FUNCTION();
		delete& s_Date;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		JM_PROFILE_FUNCTION();

		s_Date.TextureShader->Bind();
		s_Date.TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		s_Date.InstanceCount = 0;
		s_Date.TexSlotIndex = 1;
	}

	void Renderer2D::EndScene()
	{
		JM_PROFILE_FUNCTION();
		s_Date.m_JM_SquareVB_Color_TexInd_Tile_Model->SetData((void*)&s_Date.CTTM, sizeof(JM_CTTM) * s_Date.InstanceCount);
		
		Flush();
	}

	void Renderer2D::Flush()
	{
		for (int i = 0; i < s_Date.TexSlotIndex; i++)
			s_Date.TextureSlots[i]->Bind(i);
		s_Date.m_WhiteTex->Bind(0);
		s_Date.m_SquareVA->Bind();
		RenderCommand::DrawIndexedInstanced(s_Date.m_SquareVA, 0, s_Date.InstanceCount);
	}

	void Renderer2D::DrawTransQuad(const glm::mat4& model, Texture2D* texture, float tilingFactor, const glm::vec4& tintColor)
	{
		JM_PROFILE_FUNCTION();

		if (s_Date.InstanceCount >= s_Date.MaxSquareSize)
			return;

		texture = texture ? texture : s_Date.m_WhiteTex.get();

		float textureIndex = -1.0f;
		for (uint32_t i = 0; i < s_Date.TexSlotIndex; i++)
		{
			if (*s_Date.TextureSlots[i] == *texture)
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == -1.0f)
		{
			textureIndex = s_Date.TexSlotIndex;
			s_Date.TextureSlots[s_Date.TexSlotIndex] = texture;
			s_Date.TexSlotIndex++;
		}


		s_Date.CTTM[s_Date.InstanceCount].color = tintColor;
		s_Date.CTTM[s_Date.InstanceCount].texIndex = textureIndex;
		s_Date.CTTM[s_Date.InstanceCount].tiling = tilingFactor;

		s_Date.CTTM[s_Date.InstanceCount].model = model;

		s_Date.InstanceCount++;
	}

}