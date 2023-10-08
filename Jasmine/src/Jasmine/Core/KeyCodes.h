#pragma once

namespace Jasmine
{
	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

// From glfw3.h
#define JM_KEY_SPACE           ::Jasmine::Key::Space
#define JM_KEY_APOSTROPHE      ::Jasmine::Key::Apostrophe    /* ' */
#define JM_KEY_COMMA           ::Jasmine::Key::Comma         /* , */
#define JM_KEY_MINUS           ::Jasmine::Key::Minus         /* - */
#define JM_KEY_PERIOD          ::Jasmine::Key::Period        /* . */
#define JM_KEY_SLASH           ::Jasmine::Key::Slash         /* / */
#define JM_KEY_0               ::Jasmine::Key::D0
#define JM_KEY_1               ::Jasmine::Key::D1
#define JM_KEY_2               ::Jasmine::Key::D2
#define JM_KEY_3               ::Jasmine::Key::D3
#define JM_KEY_4               ::Jasmine::Key::D4
#define JM_KEY_5               ::Jasmine::Key::D5
#define JM_KEY_6               ::Jasmine::Key::D6
#define JM_KEY_7               ::Jasmine::Key::D7
#define JM_KEY_8               ::Jasmine::Key::D8
#define JM_KEY_9               ::Jasmine::Key::D9
#define JM_KEY_SEMICOLON       ::Jasmine::Key::Semicolon     /* ; */
#define JM_KEY_EQUAL           ::Jasmine::Key::Equal         /* = */
#define JM_KEY_A               ::Jasmine::Key::A
#define JM_KEY_B               ::Jasmine::Key::B
#define JM_KEY_C               ::Jasmine::Key::C
#define JM_KEY_D               ::Jasmine::Key::D
#define JM_KEY_E               ::Jasmine::Key::E
#define JM_KEY_F               ::Jasmine::Key::F
#define JM_KEY_G               ::Jasmine::Key::G
#define JM_KEY_H               ::Jasmine::Key::H
#define JM_KEY_I               ::Jasmine::Key::I
#define JM_KEY_J               ::Jasmine::Key::J
#define JM_KEY_K               ::Jasmine::Key::K
#define JM_KEY_L               ::Jasmine::Key::L
#define JM_KEY_M               ::Jasmine::Key::M
#define JM_KEY_N               ::Jasmine::Key::N
#define JM_KEY_O               ::Jasmine::Key::O
#define JM_KEY_P               ::Jasmine::Key::P
#define JM_KEY_Q               ::Jasmine::Key::Q
#define JM_KEY_R               ::Jasmine::Key::R
#define JM_KEY_S               ::Jasmine::Key::S
#define JM_KEY_T               ::Jasmine::Key::T
#define JM_KEY_U               ::Jasmine::Key::U
#define JM_KEY_V               ::Jasmine::Key::V
#define JM_KEY_W               ::Jasmine::Key::W
#define JM_KEY_X               ::Jasmine::Key::X
#define JM_KEY_Y               ::Jasmine::Key::Y
#define JM_KEY_Z               ::Jasmine::Key::Z
#define JM_KEY_LEFT_BRACKET    ::Jasmine::Key::LeftBracket   /* [ */
#define JM_KEY_BACKSLASH       ::Jasmine::Key::Backslash     /* \ */
#define JM_KEY_RIGHT_BRACKET   ::Jasmine::Key::RightBracket  /* ] */
#define JM_KEY_GRAVE_ACCENT    ::Jasmine::Key::GraveAccent   /* ` */
#define JM_KEY_WORLD_1         ::Jasmine::Key::World1        /* non-US #1 */
#define JM_KEY_WORLD_2         ::Jasmine::Key::World2        /* non-US #2 */

/* Function keys */
#define JM_KEY_ESCAPE          ::Jasmine::Key::Escape
#define JM_KEY_ENTER           ::Jasmine::Key::Enter
#define JM_KEY_TAB             ::Jasmine::Key::Tab
#define JM_KEY_BACKSPACE       ::Jasmine::Key::Backspace
#define JM_KEY_INSERT          ::Jasmine::Key::Insert
#define JM_KEY_DELETE          ::Jasmine::Key::Delete
#define JM_KEY_RIGHT           ::Jasmine::Key::Right
#define JM_KEY_LEFT            ::Jasmine::Key::Left
#define JM_KEY_DOWN            ::Jasmine::Key::Down
#define JM_KEY_UP              ::Jasmine::Key::Up
#define JM_KEY_PAGE_UP         ::Jasmine::Key::PageUp
#define JM_KEY_PAGE_DOWN       ::Jasmine::Key::PageDown
#define JM_KEY_HOME            ::Jasmine::Key::Home
#define JM_KEY_END             ::Jasmine::Key::End
#define JM_KEY_CAPS_LOCK       ::Jasmine::Key::CapsLock
#define JM_KEY_SCROLL_LOCK     ::Jasmine::Key::ScrollLock
#define JM_KEY_NUM_LOCK        ::Jasmine::Key::NumLock
#define JM_KEY_PRINT_SCREEN    ::Jasmine::Key::PrintScreen
#define JM_KEY_PAUSE           ::Jasmine::Key::Pause
#define JM_KEY_F1              ::Jasmine::Key::F1
#define JM_KEY_F2              ::Jasmine::Key::F2
#define JM_KEY_F3              ::Jasmine::Key::F3
#define JM_KEY_F4              ::Jasmine::Key::F4
#define JM_KEY_F5              ::Jasmine::Key::F5
#define JM_KEY_F6              ::Jasmine::Key::F6
#define JM_KEY_F7              ::Jasmine::Key::F7
#define JM_KEY_F8              ::Jasmine::Key::F8
#define JM_KEY_F9              ::Jasmine::Key::F9
#define JM_KEY_F10             ::Jasmine::Key::F10
#define JM_KEY_F11             ::Jasmine::Key::F11
#define JM_KEY_F12             ::Jasmine::Key::F12
#define JM_KEY_F13             ::Jasmine::Key::F13
#define JM_KEY_F14             ::Jasmine::Key::F14
#define JM_KEY_F15             ::Jasmine::Key::F15
#define JM_KEY_F16             ::Jasmine::Key::F16
#define JM_KEY_F17             ::Jasmine::Key::F17
#define JM_KEY_F18             ::Jasmine::Key::F18
#define JM_KEY_F19             ::Jasmine::Key::F19
#define JM_KEY_F20             ::Jasmine::Key::F20
#define JM_KEY_F21             ::Jasmine::Key::F21
#define JM_KEY_F22             ::Jasmine::Key::F22
#define JM_KEY_F23             ::Jasmine::Key::F23
#define JM_KEY_F24             ::Jasmine::Key::F24
#define JM_KEY_F25             ::Jasmine::Key::F25

/* Keypad */
#define JM_KEY_KP_0            ::Jasmine::Key::KP0
#define JM_KEY_KP_1            ::Jasmine::Key::KP1
#define JM_KEY_KP_2            ::Jasmine::Key::KP2
#define JM_KEY_KP_3            ::Jasmine::Key::KP3
#define JM_KEY_KP_4            ::Jasmine::Key::KP4
#define JM_KEY_KP_5            ::Jasmine::Key::KP5
#define JM_KEY_KP_6            ::Jasmine::Key::KP6
#define JM_KEY_KP_7            ::Jasmine::Key::KP7
#define JM_KEY_KP_8            ::Jasmine::Key::KP8
#define JM_KEY_KP_9            ::Jasmine::Key::KP9
#define JM_KEY_KP_DECIMAL      ::Jasmine::Key::KPDecimal
#define JM_KEY_KP_DIVIDE       ::Jasmine::Key::KPDivide
#define JM_KEY_KP_MULTIPLY     ::Jasmine::Key::KPMultiply
#define JM_KEY_KP_SUBTRACT     ::Jasmine::Key::KPSubtract
#define JM_KEY_KP_ADD          ::Jasmine::Key::KPAdd
#define JM_KEY_KP_ENTER        ::Jasmine::Key::KPEnter
#define JM_KEY_KP_EQUAL        ::Jasmine::Key::KPEqual

#define JM_KEY_LEFT_SHIFT      ::Jasmine::Key::LeftShift
#define JM_KEY_LEFT_CONTROL    ::Jasmine::Key::LeftControl
#define JM_KEY_LEFT_ALT        ::Jasmine::Key::LeftAlt
#define JM_KEY_LEFT_SUPER      ::Jasmine::Key::LeftSuper
#define JM_KEY_RIGHT_SHIFT     ::Jasmine::Key::RightShift
#define JM_KEY_RIGHT_CONTROL   ::Jasmine::Key::RightControl
#define JM_KEY_RIGHT_ALT       ::Jasmine::Key::RightAlt
#define JM_KEY_RIGHT_SUPER     ::Jasmine::Key::RightSuper
#define JM_KEY_MENU            ::Jasmine::Key::Menu