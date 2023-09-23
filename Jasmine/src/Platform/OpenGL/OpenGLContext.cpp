#include "JM_PCH.h"
#include "OpenGLContext.h"


#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

namespace Jasmine {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		JM_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		JM_CORE_ASSERT(status, "Failed to initialize Glad!");

		JM_CORE_INFO("OpenGL Info:");
		JM_CORE_INFO("  Vendor: {0}", (char*)glGetString(GL_VENDOR));
		JM_CORE_INFO("  Renderer: {0}", (char*)glGetString(GL_RENDERER));
		JM_CORE_INFO("  Version: {0}", (char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}