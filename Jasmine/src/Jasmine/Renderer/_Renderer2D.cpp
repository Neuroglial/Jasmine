#include "JM_PCH.h"
#include "_Renderer2D.h"

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
		int texIndex;
		float tiling;
		glm::mat4 model;
	};

	struct JM_Renderer2DDate {
		const static uint32_t MaxSquareSize = 10000;
		const uint32_t MaxCTTMSize = MaxSquareSize * (4 + 1 + 1 + 16);

		JM_CTTM CTTM[MaxSquareSize];

		uint32_t InstanceCount;

		JM_SP(Shader) TextureShader;
		JM_SP(Texture2D) m_WhiteTex;
		JM_SP(VertexArray) m_SquareVA;
		JM_SP(IndexBuffer) m_SquareIB;
		JM_SP(VertexBuffer) m_JM_SquareVB_Pos_TexC;
		JM_SP(VertexBuffer) m_JM_SquareVB_Color_TexInd_Tile_Model;
	};

	static JM_Renderer2DDate& s_Date = *(new JM_Renderer2DDate());

	void Renderer2D::Init()
	{
		JM_PROFILE_FUNCTION();

		// Create the White Texture;
		s_Date.m_WhiteTex = Texture2D::Create(1, 1);
		uint32_t w_data = 0xffffffff;
		s_Date.m_WhiteTex->SetData(&w_data, sizeof(uint32_t));

		// Create VertexArray
		s_Date.m_SquareVA = VertexArray::Create();
		JM_SquareVB svb;
		s_Date.m_JM_SquareVB_Pos_TexC = VertexBuffer::Create((float*)&svb, sizeof(svb) / sizeof(float));
		s_Date.m_JM_SquareVB_Pos_TexC->SetLayout(
			{ {ShaderDataType::Float3, "a_Position;"},
			  {ShaderDataType::Float4, "a_TexCoord;"}});
		s_Date.m_JM_SquareVB_Color_TexInd_Tile_Model = VertexBuffer::Create(s_Date.MaxCTTMSize);
		s_Date.m_JM_SquareVB_Color_TexInd_Tile_Model->SetLayout(
			{ {ShaderDataType::Float4, "a_Color"},
			  {ShaderDataType::Int,	   "a_TexIndex"},
			  {ShaderDataType::Float,  "a_TilingFactor"},
			  {ShaderDataType::Mat4,   "a_Model"} });
		s_Date.m_JM_SquareVB_Color_TexInd_Tile_Model->SetAtrribDivisorFactor(1);
		JM_SquareEB seb;
		s_Date.m_SquareIB = IndexBuffer::Create((uint32_t*)&seb, sizeof(seb) / sizeof(uint32_t));
		s_Date.m_SquareVA->AddVertexBuffer(s_Date.m_JM_SquareVB_Pos_TexC);
		s_Date.m_SquareVA->AddVertexBuffer(s_Date.m_JM_SquareVB_Color_TexInd_Tile_Model);
		s_Date.m_SquareVA->SetIndexBuffer(s_Date.m_SquareIB);

		s_Date.TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		s_Date.TextureShader->SetInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		JM_PROFILE_FUNCTION();
		delete &s_Date;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		JM_PROFILE_FUNCTION();

		s_Date.TextureShader->Bind();
		s_Date.TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		s_Date.InstanceCount = 0;
	}

	void Renderer2D::EndScene()
	{
		JM_PROFILE_FUNCTION();
		s_Date.m_JM_SquareVB_Color_TexInd_Tile_Model->SetData((void*)&s_Date.CTTM, sizeof(JM_CTTM) * s_Date.InstanceCount);
		Flush;
	}

	void Renderer2D::Flush()
	{
		s_Date.m_WhiteTex->Bind(0);
		RenderCommand::DrawIndexedInstanced(s_Date.m_SquareVA, NULL, s_Date.InstanceCount);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Texture2D* texture, float tilingFactor, const glm::vec4& tintColor)
	{
		auto& theCTTM = s_Date.CTTM[s_Date.InstanceCount];

		theCTTM.color = tintColor;
		theCTTM.texIndex = 0;
		theCTTM.tiling = tilingFactor;
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
							* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
							* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		theCTTM.model = transform;

		s_Date.InstanceCount++;
	}

}