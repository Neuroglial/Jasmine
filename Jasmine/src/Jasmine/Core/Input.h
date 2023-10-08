#pragma once

#include "JM_PCH.h"
#include <glm/glm.hpp>
#include "Jasmine/Core/KeyCodes.h"
#include "Jasmine/Core/MouseCodes.h"

namespace Jasmine {

	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode keycode);
		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
		static glm::vec2 GetWindowSize();
	};

}