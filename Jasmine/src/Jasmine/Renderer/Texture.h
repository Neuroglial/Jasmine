#pragma once

#include <string>

#include "Jasmine/Core.h"

namespace Jasmine {

	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static JM_SP(Texture2D) Create(const std::string& path);
	};

}