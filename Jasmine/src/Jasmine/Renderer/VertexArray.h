#pragma once

#include "JM_PCH.h"
#include "Jasmine/Renderer/Buffer.h"

namespace Jasmine {

	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const JM_SP(VertexBuffer)& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const JM_SP(IndexBuffer)& indexBuffer) = 0;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;

		static JM_SP(VertexArray) Create();
	};

}

