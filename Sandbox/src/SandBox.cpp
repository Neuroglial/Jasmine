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
		if (Jasmine::Input::IsKeyPressed(JM_KEY_TAB))
			JM_TRACE("Tab key is pressed (poll)!");
	}

	void OnEvent(Jasmine::Event& e) override
	{
		if (e.GetEventType() == Jasmine::EventType::KeyPressed)
		{
			auto& ev = JM_CONVERT(Jasmine::KeyPressedEvent, e);
			if (ev.GetKeyCode() == JM_KEY_TAB)
				JM_TRACE("Tab key is pressed (event)!");
			JM_TRACE("{0}", (char)ev.GetKeyCode());
		}
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