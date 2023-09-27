#include <Jasmine.h>

#include <Jasmine/Core/EntryPoint.h>

#include "Sandbox2D.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Jasmine::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f)
	{
		m_VertexArray = Jasmine::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		JM_SP(Jasmine::VertexBuffer) vertexBuffer;
		vertexBuffer.reset(Jasmine::VertexBuffer::Create(vertices, sizeof(vertices)));
		Jasmine::BufferLayout layout = {
			{ Jasmine::ShaderDataType::Float3, "a_Position" },
			{ Jasmine::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		JM_SP(Jasmine::IndexBuffer) indexBuffer;
		indexBuffer.reset(Jasmine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA = Jasmine::VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		JM_SP(Jasmine::VertexBuffer) squareVB;
		squareVB.reset(Jasmine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Jasmine::ShaderDataType::Float3, "a_Position" },
			{ Jasmine::ShaderDataType::Float2, "a_TexCoord" }
		});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Jasmine::IndexBuffer> squareIB;
		squareIB.reset(Jasmine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		SL.Load("assets/shaders/TextureShader.glsl");
		SL.Load("assets/shaders/BasicShader.glsl");

		m_Texture = Jasmine::Texture2D::Create("assets/textures/Checkerboard.png");
		m_AwesomefaceTexture = Jasmine::Texture2D::Create("assets/textures/awesomeface.png");
		m_JM_logo = Jasmine::Texture2D::Create("assets/textures/JM_logo.png");

		SL.GetCast<Jasmine::OpenGLShader>("TextureShader")->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Jasmine::Timestep ts) override
	{
		m_CameraController.OnUpdate(ts);

		Jasmine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Jasmine::RenderCommand::Clear();

		Jasmine::Renderer::BeginScene(m_CameraController.GetCamera());

		m_Texture->Bind(0);
		Jasmine::Renderer::Submit(SL.Get("TextureShader"), m_SquareVA);

		m_AwesomefaceTexture->Bind(0);
		Jasmine::Renderer::Submit(SL.Get("TextureShader"), m_SquareVA);

		Jasmine::Renderer::Submit(SL.Get("BasicShader"), m_VertexArray);

		Jasmine::Renderer::EndScene();
	}

	void OnEvent(Jasmine::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}

	private:
		std::shared_ptr<Jasmine::Shader> m_Shader;
		std::shared_ptr<Jasmine::VertexArray> m_VertexArray;

		std::shared_ptr<Jasmine::Shader> m_TextureShader;
		std::shared_ptr<Jasmine::VertexArray> m_SquareVA;

		JM_SP(Jasmine::Texture2D) m_Texture, m_AwesomefaceTexture, m_JM_logo;
		Jasmine::ShaderLibrary SL;

		//Jasmine::OrthographicCamera m_Camera;
		Jasmine::OrthographicCameraController m_CameraController;
		glm::vec3 m_CameraPosition;
		float m_CameraMoveSpeed = 5.0f;

		float m_CameraRotation = 0.0f;
		float m_CameraRotationSpeed = 180.0f;

};


class SandBox : public Jasmine::Application
{
public:
	SandBox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~SandBox()
	{

	}
};

Jasmine::Application* Jasmine::CreateApplication()
{
	return new SandBox();
}