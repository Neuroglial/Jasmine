#include "JM_PCH.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Jasmine {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Jasmine::ShaderDataType::Float:    return GL_FLOAT;
		case Jasmine::ShaderDataType::Float2:   return GL_FLOAT;
		case Jasmine::ShaderDataType::Float3:   return GL_FLOAT;
		case Jasmine::ShaderDataType::Float4:   return GL_FLOAT;
		case Jasmine::ShaderDataType::Mat3:     return GL_FLOAT;
		case Jasmine::ShaderDataType::Mat4:     return GL_FLOAT;
		case Jasmine::ShaderDataType::Int:      return GL_INT;
		case Jasmine::ShaderDataType::Int2:     return GL_INT;
		case Jasmine::ShaderDataType::Int3:     return GL_INT;
		case Jasmine::ShaderDataType::Int4:     return GL_INT;
		case Jasmine::ShaderDataType::Bool:     return GL_BOOL;
		}

		JM_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		JM_PROFILE_FUNCTION();

		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		JM_PROFILE_FUNCTION();

		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		JM_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		JM_PROFILE_FUNCTION();

		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		JM_PROFILE_FUNCTION();

		JM_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			if (vertexBuffer->GetAtrribDivisorFactor())
				glVertexAttribDivisor(index, vertexBuffer->GetAtrribDivisorFactor());
			index++;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		JM_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

}