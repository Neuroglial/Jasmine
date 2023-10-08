#include "JM_PCH.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Jasmine {

	void Renderer2D::Init()
	{
		JM_PROFILE_FUNCTION();

		// Create the White Texture;
		s_Data.m_WhiteTex = Texture2D::Create(1, 1);
		uint32_t w_data = 0xffffffff;
		s_Data.m_WhiteTex->SetData(&w_data, sizeof(uint32_t));
		s_Data.TextureSlots[0] = s_Data.m_WhiteTex.get();

		// Create VertexArray
		s_Data.m_SquareVA = VertexArray::Create();
		float svb[] = {
			 0.0f, 0.0f, 0.0f ,   0.0f, 0.0f ,
			 1.0f, 0.0f, 0.0f ,   1.0f, 0.0f ,
			 1.0f, 1.0f, 0.0f ,   1.0f, 1.0f ,
			 0.0f, 1.0f, 0.0f ,   0.0f, 1.0f
		};

		s_Data.m_JM_SquareVB_PT = VertexBuffer::Create(svb, sizeof(svb));
		s_Data.m_JM_SquareVB_PT->SetLayout(
			{ {ShaderDataType::Float3, "Position;"},
			  {ShaderDataType::Float2, "TexCoord;"} });
		
		s_Data.m_JM_SquareVB_PSRCTT = VertexBuffer::Create(sizeof(s_Data.Buffer));
		s_Data.m_JM_SquareVB_PSRCTT->SetLayout(
			{ {ShaderDataType::Float3, "s_Position"},
			  {ShaderDataType::Float2, "s_Size"},
			  {ShaderDataType::Float,  "s_Rotate"},
			  {ShaderDataType::Float4, "s_Color"},
			  {ShaderDataType::Float,  "s_TexIndex"} ,
			  {ShaderDataType::Float,  "s_TilingFactor"} });
		s_Data.m_JM_SquareVB_PSRCTT->SetAtrribDivisorFactor(1);
		
		uint32_t seb[] = {
			0,1,2, 0,2,3
		};

		s_Data.m_SquareIB = IndexBuffer::Create(seb, sizeof(seb) / sizeof(uint32_t));
		s_Data.m_SquareVA->AddVertexBuffer(s_Data.m_JM_SquareVB_PT);
		s_Data.m_SquareVA->AddVertexBuffer(s_Data.m_JM_SquareVB_PSRCTT);
		s_Data.m_SquareVA->SetIndexBuffer(s_Data.m_SquareIB);

		s_Data.TextureShader = Shader::Create("assets/shaders/TextureShader.glsl");
		
		int texs[32];
		for (int i = 0; i < 32; i++)
			texs[i] = i;
		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetIntArray("u_Textures", texs, 32);
	}

	void Renderer2D::Shutdown()
	{
		JM_PROFILE_FUNCTION();
		delete& s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		JM_PROFILE_FUNCTION();

		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		s_Data.InstanceCount = 0;
		s_Data.TexSlotIndex = 1;
		ResetStats();
	}

	void Renderer2D::EndScene()
	{
		JM_PROFILE_FUNCTION();

		int index = 0;
		for (auto& i : s_Data.PSRCTT) {
			s_Data.Buffer[index++] = i.second;
		}
		s_Data.PSRCTT.clear();
		s_Data.m_JM_SquareVB_PSRCTT->SetData((void*)&s_Data.Buffer, sizeof(JM_PSRCTT) * s_Data.InstanceCount);
		
		Flush();
	}

	void Renderer2D::Flush()
	{
		JM_PROFILE_FUNCTION();
		for (int i = 0; i < s_Data.TexSlotIndex; i++)
			s_Data.TextureSlots[i]->Bind(i);
		s_Data.m_SquareVA->Bind();
		RenderCommand::DrawIndexedInstanced(s_Data.m_SquareVA, 0, s_Data.InstanceCount);
	}

	void Renderer2D::FlushAndReset()
	{
		EndScene();

		s_Data.InstanceCount = 0;
		s_Data.TexSlotIndex = 1;
	}

	void Renderer2D::ResetStats()
	{
		memset(&s_Data.Stats, 0, sizeof(Statistics));
	}

	Renderer2D::Statistics Renderer2D::GetStats()
	{
		return s_Data.Stats;
	}

}