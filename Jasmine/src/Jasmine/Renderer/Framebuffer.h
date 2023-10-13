#pragma once

#include "Jasmine/Core/Base.h"
#include <glm/glm.hpp>
#include <iostream>

namespace Jasmine {

	struct FramebufferSpecification
	{
		uint32_t Width = 0, Height = 0;
		// FramebufferFormat Format = 
		uint32_t Samples = 1;

		bool SwapChainTarget = false;
	};

	class Framebuffer
	{
	public:
		Framebuffer(const FramebufferSpecification& spec) :m_Specification(spec) {}
		const glm::vec2 GetBufferSize() { return{ m_Specification.Width,m_Specification.Height }; }
		

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual uint32_t GetColorAttachmentRendererID() const = 0;

		virtual const FramebufferSpecification& GetSpecification() const = 0;
		virtual void Resize(uint32_t width, uint32_t height) = 0;

		static JM_SP(Framebuffer) Create(const FramebufferSpecification& spec);
	protected:
		FramebufferSpecification m_Specification;
	};


}