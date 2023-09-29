#include <Jasmine.h>

#include <Jasmine/Core/EntryPoint.h>
#include "Sandbox2D.h"



class SandBox : public Jasmine::Application
{
public:
	SandBox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~SandBox()
	{

	}
};

Jasmine::Application* Jasmine::CreateApplication()
{
	return new SandBox();
}