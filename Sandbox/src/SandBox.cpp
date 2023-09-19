#include <Jasmine.h>

class SandBox : public Jasmine::Application
{
public:
	SandBox()
	{

	}

	~SandBox()
	{

	}
};

Jasmine::Application* Jasmine::CreateApplication()
{
	return new SandBox();
}