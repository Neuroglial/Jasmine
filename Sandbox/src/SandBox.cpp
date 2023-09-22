#include <Jasmine.h>

class ExampleLayer : public Jasmine::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		JM_INFO("ExampleLayer::Update");
	}

	void OnEvent(Jasmine::Event& e) override
	{
		JM_INFO(e);
	}

};


class SandBox : public Jasmine::Application
{
public:
	SandBox()
	{
		PushLayer(new ExampleLayer());
	}

	~SandBox()
	{

	}
};

Jasmine::Application* Jasmine::CreateApplication()
{
	return new SandBox();
}