#pragma once

#include "JM_PCH.h"

#include "Jasmine/Core.h"
#include "Jasmine/Events/Event.h"

namespace Jasmine {

	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& _title = "Jasmine Engin", unsigned int _width = 1280, unsigned int _height = 720)
			:Title(_title), Width(_width), Height(_height) {}

	};

	class JASMINE_API Window 
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}
		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		//Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool Enable) = 0;
		virtual bool IsVSync() const = 0;
		virtual void* GetNativeWindow() const = 0;


		static Window* Create(WindowProps& props = WindowProps());
	};

}