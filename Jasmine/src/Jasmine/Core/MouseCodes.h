#pragma once

namespace Jasmine
{
	typedef enum class MouseCode : uint16_t
	{
		// From glfw3.h
		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Button6 = 6,
		Button7 = 7,

		ButtonLast = Button7,
		ButtonLeft = Button0,
		ButtonRight = Button1,
		ButtonMiddle = Button2
	} Mouse;

	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}

#define JM_MOUSE_BUTTON_0      ::Jasmine::Mouse::Button0
#define JM_MOUSE_BUTTON_1      ::Jasmine::Mouse::Button1
#define JM_MOUSE_BUTTON_2      ::Jasmine::Mouse::Button2
#define JM_MOUSE_BUTTON_3      ::Jasmine::Mouse::Button3
#define JM_MOUSE_BUTTON_4      ::Jasmine::Mouse::Button4
#define JM_MOUSE_BUTTON_5      ::Jasmine::Mouse::Button5
#define JM_MOUSE_BUTTON_6      ::Jasmine::Mouse::Button6
#define JM_MOUSE_BUTTON_7      ::Jasmine::Mouse::Button7
#define JM_MOUSE_BUTTON_LAST   ::Jasmine::Mouse::ButtonLast
#define JM_MOUSE_BUTTON_LEFT   ::Jasmine::Mouse::ButtonLeft
#define JM_MOUSE_BUTTON_RIGHT  ::Jasmine::Mouse::ButtonRight
#define JM_MOUSE_BUTTON_MIDDLE ::Jasmine::Mouse::ButtonMiddle