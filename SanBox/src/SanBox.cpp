#include <Jasmine.h>

class SanBox : public Jasmine::Application
{
public:
	SanBox() 
	{

	}

	~SanBox() 
	{

	}
};

Jasmine::Application* Jasmine::CreateApplication()
{
	return new SanBox();
}