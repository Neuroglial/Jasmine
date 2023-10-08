#include "JM_PCH.h"
#include "OrthographicCamera.h"

#include "Jasmine/Core/Window.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Jasmine/Core/Input.h"

namespace Jasmine {

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: m_ViewMatrix(1.0f)
	{
		JM_PROFILE_FUNCTION();
		SetProjection(left, right, bottom, top);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
	{
		JM_PROFILE_FUNCTION();

		m_ProjectionMatrix = glm::ortho(left, right, invertY * bottom, invertY * top, -1.0f, 1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	glm::vec2 OrthographicCamera::GetMousePos(glm::vec2 mousepos)
	{
		auto inv = glm::inverse(m_ViewProjectionMatrix);

		auto ws = Input::GetWindowSize();

		mousepos = { mousepos.x / ws.first,1.0f - mousepos.y / ws.second };
		mousepos = mousepos * 2.0f - 1.0f;

		glm::vec4 temp = inv * glm::vec4(mousepos.x, mousepos.y, 0.0f, 1.0f);

		return { temp.x, temp.y };
	}

	void OrthographicCamera::SetInvertY(bool enable)
	{
		if (enable)
			invertY = -1.0f;
		else
			invertY = 1.0f;
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		JM_PROFILE_FUNCTION();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}