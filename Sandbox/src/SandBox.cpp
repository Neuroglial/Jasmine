#include <Jasmine.h>

#include <Jasmine/Core/EntryPoint.h>
#include "Sandbox2D.h"
#include <omp.h>


class SandBox : public Jasmine::Application
{
public:
	SandBox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
		omp_set_num_threads(8);
	}

	~SandBox()
	{

	}
};

Jasmine::Application* Jasmine::CreateApplication()
{
	return new SandBox();
}