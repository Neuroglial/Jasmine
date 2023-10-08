#pragma once

#include "JM_PCH.h"
#include "Jasmine/Core/Core.h"
#include "Jasmine/Core/KeyCodes.h"
#include "Jasmine/Core/MouseCodes.h"

namespace Jasmine {

	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode keycode);
		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
		static std::pair<int, int> GetWindowSize();
	};

}