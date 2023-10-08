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
		JM_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		JM_CORE_ASSERT(status, "Failed to initialize Glad!");

		JM_CORE_INFO("---------------OpenGL Info------------------------------------");
		JM_CORE_INFO(" Vendor:   {0}", (char*)glGetString(GL_VENDOR));
		JM_CORE_INFO(" Renderer: {0}", (char*)glGetString(GL_RENDERER));
		JM_CORE_INFO(" Version:  {0}", (char*)glGetString(GL_VERSION));
		JM_CORE_INFO("--------------------------------------------------------------");

		

		int w, h;
		glfwGetWindowSize(m_WindowHandle, &w, &h);
		glViewport(0, 0, w, h);

		JM_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "Hazel requires at least OpenGL version 4.5!");
	}

	void OpenGLContext::SwapBuffers()
	{
		JM_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}

}