#include "JM_PCH.h"
#include "Jasmine/Core/Input.h"

#include "Jasmine/Core/Application.h"
#include <GLFW/glfw3.h>

namespace Jasmine {

	bool Input::IsKeyPressed(const KeyCode key)
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, static_cast<int32_t>(key));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(const MouseCode button)
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
		return state == GLFW_PRESS;
	}

	glm::vec2 Input::GetMousePosition()
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float Input::GetMouseX()
	{
		auto pos = GetMousePosition();
		return pos.x;
	}

	float Input::GetMouseY()
	{
		auto pos = GetMousePosition();
		return pos.y;
	}

	glm::vec2 Input::GetWindowSize()
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int w, h;
		glfwGetWindowSize(window, &w, &h);
		return { w, h };
	}

}
