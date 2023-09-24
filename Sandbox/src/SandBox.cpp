#include <Jasmine.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Jasmine::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Jasmine::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<Jasmine::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Jasmine::VertexBuffer::Create(vertices, sizeof(vertices)));
		Jasmine::BufferLayout layout = {
			{ Jasmine::ShaderDataType::Float3, "a_Position" },
			{ Jasmine::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Jasmine::IndexBuffer> indexBuffer;
		indexBuffer.reset(Jasmine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Jasmine::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<Jasmine::VertexBuffer> squareVB;
		squareVB.reset(Jasmine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Jasmine::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Jasmine::IndexBuffer> squareIB;
		squareIB.reset(Jasmine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			uniform mat4 u_ViewProjection;
			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(Jasmine::Shader::Create(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			uniform mat4 u_ViewProjection;
			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(Jasmine::Shader::Create(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	void OnUpdate(Jasmine::Timestep ts) override
	{
		if (Jasmine::Input::IsKeyPressed(JM_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Jasmine::Input::IsKeyPressed(JM_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Jasmine::Input::IsKeyPressed(JM_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (Jasmine::Input::IsKeyPressed(JM_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Jasmine::Input::IsKeyPressed(JM_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		if (Jasmine::Input::IsKeyPressed(JM_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		Jasmine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Jasmine::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Jasmine::Renderer::BeginScene(m_Camera);

		Jasmine::Renderer::Submit(m_BlueShader, m_SquareVA);
		Jasmine::Renderer::Submit(m_Shader, m_VertexArray);

		Jasmine::Renderer::EndScene();
	}

	void OnEvent(Jasmine::Event& e) override
	{
		if (e.GetEventType() == Jasmine::EventType::KeyPressed)
		{
			auto& ev = JM_CONVERT(Jasmine::KeyPressedEvent, e);
			if (ev.GetKeyCode() == JM_KEY_TAB)
				JM_TRACE("Tab key is pressed (event)!");
			//JM_TRACE("{0}", (char)ev.GetKeyCode());
		}
	}

	private:
		std::shared_ptr<Jasmine::Shader> m_Shader;
		std::shared_ptr<Jasmine::VertexArray> m_VertexArray;

		std::shared_ptr<Jasmine::Shader> m_BlueShader;
		std::shared_ptr<Jasmine::VertexArray> m_SquareVA;

		Jasmine::OrthographicCamera m_Camera;
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
		PushLayer(new ExampleLayer());
	}

	~SandBox()
	{

	}
};

Jasmine::Application* Jasmine::CreateApplication()
{
	return new SandBox();
}