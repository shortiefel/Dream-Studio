/* Start Header**********************************************************************************/
/*
@file    Input.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    31/08/2021
\brief
This file has the definition for Input


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Input/Input.hpp"
#include "Engine/Header/pch.hpp"

namespace Engine {
	//Math::vec2 Input::mousePosition;

	/*------------------------------------------------------------------------------------------------------------------------------
	GLFW to input key code map
	------------------------------------------------------------------------------------------------------------------------------*/
	std::unordered_map<int, Input_KeyCode> Input::GLFWtoInputKey{
		{ GLFW_KEY_0, Input_KeyCode::T0 },
		{ GLFW_KEY_1, Input_KeyCode::T1 },
		{ GLFW_KEY_2, Input_KeyCode::T2 },
		{ GLFW_KEY_3, Input_KeyCode::T3 },
		{ GLFW_KEY_4, Input_KeyCode::T4 },
		{ GLFW_KEY_5, Input_KeyCode::T5 },
		{ GLFW_KEY_6, Input_KeyCode::T6 },
		{ GLFW_KEY_7, Input_KeyCode::T7 },
		{ GLFW_KEY_8, Input_KeyCode::T8 },
		{ GLFW_KEY_9, Input_KeyCode::T9 },

		{ GLFW_KEY_A, Input_KeyCode::A },
		{ GLFW_KEY_B, Input_KeyCode::B },
		{ GLFW_KEY_C, Input_KeyCode::C },
		{ GLFW_KEY_D, Input_KeyCode::D },
		{ GLFW_KEY_E, Input_KeyCode::E },
		{ GLFW_KEY_F, Input_KeyCode::F },
		{ GLFW_KEY_G, Input_KeyCode::G },
		{ GLFW_KEY_H, Input_KeyCode::H },
		{ GLFW_KEY_I, Input_KeyCode::I },
		{ GLFW_KEY_J, Input_KeyCode::J },
		{ GLFW_KEY_K, Input_KeyCode::K },
		{ GLFW_KEY_L, Input_KeyCode::L },
		{ GLFW_KEY_M, Input_KeyCode::M },
		{ GLFW_KEY_N, Input_KeyCode::N },
		{ GLFW_KEY_O, Input_KeyCode::O },
		{ GLFW_KEY_P, Input_KeyCode::P },
		{ GLFW_KEY_Q, Input_KeyCode::Q },
		{ GLFW_KEY_R, Input_KeyCode::R },
		{ GLFW_KEY_S, Input_KeyCode::S },
		{ GLFW_KEY_T, Input_KeyCode::T },
		{ GLFW_KEY_U, Input_KeyCode::U },
		{ GLFW_KEY_V, Input_KeyCode::V },
		{ GLFW_KEY_W, Input_KeyCode::W },
		{ GLFW_KEY_X, Input_KeyCode::X },
		{ GLFW_KEY_Y, Input_KeyCode::Y },
		{ GLFW_KEY_Z, Input_KeyCode::Z },

		//Function keys
		{ GLFW_KEY_F1 , Input_KeyCode::F1 },
		{ GLFW_KEY_F2 , Input_KeyCode::F2 },
		{ GLFW_KEY_F3 , Input_KeyCode::F3 },
		{ GLFW_KEY_F4 , Input_KeyCode::F4 },
		{ GLFW_KEY_F5 , Input_KeyCode::F5 },
		{ GLFW_KEY_F6 , Input_KeyCode::F6 },
		{ GLFW_KEY_F7 , Input_KeyCode::F7 },
		{ GLFW_KEY_F8 , Input_KeyCode::F8 },
		{ GLFW_KEY_F9 , Input_KeyCode::F9 },
		{ GLFW_KEY_F10, Input_KeyCode::F10 },
		{ GLFW_KEY_F11, Input_KeyCode::F11 },
		{ GLFW_KEY_F12, Input_KeyCode::F12 },
		{ GLFW_KEY_F13, Input_KeyCode::F13 },
		{ GLFW_KEY_F14, Input_KeyCode::F14 },
		{ GLFW_KEY_F15, Input_KeyCode::F15 },
		{ GLFW_KEY_F16, Input_KeyCode::F16 },
		{ GLFW_KEY_F17, Input_KeyCode::F17 },
		{ GLFW_KEY_F18, Input_KeyCode::F18 },
		{ GLFW_KEY_F19, Input_KeyCode::F19 },
		{ GLFW_KEY_F20, Input_KeyCode::F20 },
		{ GLFW_KEY_F21, Input_KeyCode::F21 },
		{ GLFW_KEY_F22, Input_KeyCode::F22 },
		{ GLFW_KEY_F23, Input_KeyCode::F23 },
		{ GLFW_KEY_F24, Input_KeyCode::F24 },

		//Left side
		{ GLFW_KEY_ESCAPE, Input_KeyCode::Escape },
		{ GLFW_KEY_GRAVE_ACCENT, Input_KeyCode::GraveAccent }, //` and ~ (Tilde)
		{ GLFW_KEY_TAB, Input_KeyCode::Tab },
		{ GLFW_KEY_CAPS_LOCK, Input_KeyCode::CapsLock },

		{ GLFW_KEY_LEFT_SHIFT, Input_KeyCode::Shift},
		{ GLFW_KEY_RIGHT_SHIFT, Input_KeyCode::Shift},
		{ GLFW_KEY_LEFT_CONTROL, Input_KeyCode::Control},
		{ GLFW_KEY_RIGHT_CONTROL, Input_KeyCode::Control},
		{ GLFW_KEY_LEFT_ALT, Input_KeyCode::Alt},
		{ GLFW_KEY_RIGHT_ALT, Input_KeyCode::Alt},

		{ GLFW_KEY_SPACE, Input_KeyCode::Space },

		//Right side
		{ GLFW_KEY_MINUS, Input_KeyCode::Minus },
		{ GLFW_KEY_EQUAL, Input_KeyCode::Equal },
		{ GLFW_KEY_BACKSPACE, Input_KeyCode::Backspace },

		{ GLFW_KEY_LEFT_BRACKET, Input_KeyCode::LeftBracket },
		{ GLFW_KEY_RIGHT_BRACKET, Input_KeyCode::RightBracket },
		{ GLFW_KEY_BACKSLASH, Input_KeyCode::BackSlash }, // \

		{ GLFW_KEY_SEMICOLON, Input_KeyCode::Semicolon },
		{ GLFW_KEY_APOSTROPHE, Input_KeyCode::Apostrophe },
		{ GLFW_KEY_ENTER, Input_KeyCode::Enter },

		{ GLFW_KEY_COMMA, Input_KeyCode::Comma },
		{ GLFW_KEY_PERIOD, Input_KeyCode::Period },
		{ GLFW_KEY_SLASH, Input_KeyCode::FrontSlash }, /* / */


		{ GLFW_KEY_PRINT_SCREEN, Input_KeyCode::PrintScreen },
		{ GLFW_KEY_SCROLL_LOCK, Input_KeyCode::ScrollLock },
		{ GLFW_KEY_PAUSE, Input_KeyCode::Pause },

		{ GLFW_KEY_INSERT, Input_KeyCode::Insert },
		{ GLFW_KEY_DELETE, Input_KeyCode::Delete },
		{ GLFW_KEY_HOME, Input_KeyCode::Home },
		{ GLFW_KEY_END, Input_KeyCode::End },
		{ GLFW_KEY_PAGE_UP, Input_KeyCode::PageUp },
		{ GLFW_KEY_PAGE_DOWN, Input_KeyCode::PageDown },

		//Arrow Keys
		{ GLFW_KEY_LEFT, Input_KeyCode::Left },
		{ GLFW_KEY_RIGHT, Input_KeyCode::Right },
		{ GLFW_KEY_UP, Input_KeyCode::Up },
		{ GLFW_KEY_DOWN, Input_KeyCode::Down },

		//Keypad
		{ GLFW_KEY_NUM_LOCK, Input_KeyCode::NumLock },
		{ GLFW_KEY_KP_0, Input_KeyCode::KP0 },
		{ GLFW_KEY_KP_1, Input_KeyCode::KP1 },
		{ GLFW_KEY_KP_2, Input_KeyCode::KP2 },
		{ GLFW_KEY_KP_3, Input_KeyCode::KP3 },
		{ GLFW_KEY_KP_4, Input_KeyCode::KP4 },
		{ GLFW_KEY_KP_5, Input_KeyCode::KP5 },
		{ GLFW_KEY_KP_6, Input_KeyCode::KP6 },
		{ GLFW_KEY_KP_7, Input_KeyCode::KP7 },
		{ GLFW_KEY_KP_8, Input_KeyCode::KP8 },
		{ GLFW_KEY_KP_9, Input_KeyCode::KP9 },
		{ GLFW_KEY_KP_DECIMAL, Input_KeyCode::KPDecimal },
		{ GLFW_KEY_KP_DIVIDE, Input_KeyCode::KPDivide },
		{ GLFW_KEY_KP_MULTIPLY, Input_KeyCode::KPMultiply },
		{ GLFW_KEY_KP_SUBTRACT, Input_KeyCode::KPSubtract },
		{ GLFW_KEY_KP_ADD, Input_KeyCode::KPAdd },
		{ GLFW_KEY_KP_ENTER, Input_KeyCode::KPEnter }
	};

	/*------------------------------------------------------------------------------------------------------------------------------
	Input key to bool map
	------------------------------------------------------------------------------------------------------------------------------*/
	std::unordered_map<Input_KeyCode, bool> Input::InputKeyStatus{
		{ Input_KeyCode::T0, false },
		{ Input_KeyCode::T1, false },
		{ Input_KeyCode::T2, false },
		{ Input_KeyCode::T3, false },
		{ Input_KeyCode::T4, false },
		{ Input_KeyCode::T5, false },
		{ Input_KeyCode::T6, false },
		{ Input_KeyCode::T7, false },
		{ Input_KeyCode::T8, false },
		{ Input_KeyCode::T9, false },

		{ Input_KeyCode::A, false },
		{ Input_KeyCode::B, false },
		{ Input_KeyCode::C, false },
		{ Input_KeyCode::D, false },
		{ Input_KeyCode::E, false },
		{ Input_KeyCode::F, false },
		{ Input_KeyCode::G, false },
		{ Input_KeyCode::H, false },
		{ Input_KeyCode::I, false },
		{ Input_KeyCode::J, false },
		{ Input_KeyCode::K, false },
		{ Input_KeyCode::L, false },
		{ Input_KeyCode::M, false },
		{ Input_KeyCode::N, false },
		{ Input_KeyCode::O, false },
		{ Input_KeyCode::P, false },
		{ Input_KeyCode::Q, false },
		{ Input_KeyCode::R, false },
		{ Input_KeyCode::S, false },
		{ Input_KeyCode::T, false },
		{ Input_KeyCode::U, false },
		{ Input_KeyCode::V, false },
		{ Input_KeyCode::W, false },
		{ Input_KeyCode::X, false },
		{ Input_KeyCode::Y, false },
		{ Input_KeyCode::Z, false },

		//Function keys
		{ Input_KeyCode::F1, false },
		{ Input_KeyCode::F2, false },
		{ Input_KeyCode::F3, false },
		{ Input_KeyCode::F4, false },
		{ Input_KeyCode::F5, false },
		{ Input_KeyCode::F6, false },
		{ Input_KeyCode::F7, false },
		{ Input_KeyCode::F8, false },
		{ Input_KeyCode::F9, false },
		{ Input_KeyCode::F10, false },
		{ Input_KeyCode::F11, false },
		{ Input_KeyCode::F12, false },
		{ Input_KeyCode::F13, false },
		{ Input_KeyCode::F14, false },
		{ Input_KeyCode::F15, false },
		{ Input_KeyCode::F16, false },
		{ Input_KeyCode::F17, false },
		{ Input_KeyCode::F18, false },
		{ Input_KeyCode::F19, false },
		{ Input_KeyCode::F20, false },
		{ Input_KeyCode::F21, false },
		{ Input_KeyCode::F22, false },
		{ Input_KeyCode::F23, false },
		{ Input_KeyCode::F24, false },

		//Left side
		{ Input_KeyCode::Escape, false },
		{ Input_KeyCode::GraveAccent, false }, //` and ~ (Tilde)
		{ Input_KeyCode::Tab, false },
		{ Input_KeyCode::CapsLock, false },

		{ Input_KeyCode::Shift, false },
		{ Input_KeyCode::Control, false },
		{ Input_KeyCode::Alt, false },

		{ Input_KeyCode::Space, false },

		//Right side
		{ Input_KeyCode::Minus, false },
		{ Input_KeyCode::Equal, false },
		{ Input_KeyCode::Backspace, false },

		{ Input_KeyCode::LeftBracket, false },
		{ Input_KeyCode::RightBracket, false },
		{ Input_KeyCode::BackSlash, false }, // \

		{ Input_KeyCode::Semicolon, false },
		{ Input_KeyCode::Apostrophe, false },
		{ Input_KeyCode::Enter, false },

		{ Input_KeyCode::Comma, false },
		{ Input_KeyCode::Period, false },
		{ Input_KeyCode::FrontSlash, false }, /* / */


		{ Input_KeyCode::PrintScreen, false },
		{ Input_KeyCode::ScrollLock, false },
		{ Input_KeyCode::Pause, false },

		{ Input_KeyCode::Insert, false },
		{ Input_KeyCode::Delete, false },
		{ Input_KeyCode::Home, false },
		{ Input_KeyCode::End, false },
		{ Input_KeyCode::PageUp, false },
		{ Input_KeyCode::PageDown, false },

		//Arrow Keys
		{ Input_KeyCode::Left, false },
		{ Input_KeyCode::Right, false },
		{ Input_KeyCode::Up, false },
		{ Input_KeyCode::Down, false },

		//Keypad
		{ Input_KeyCode::NumLock, false },
		{ Input_KeyCode::KP0, false },
		{ Input_KeyCode::KP1, false },
		{ Input_KeyCode::KP2, false },
		{ Input_KeyCode::KP3, false },
		{ Input_KeyCode::KP4, false },
		{ Input_KeyCode::KP5, false },
		{ Input_KeyCode::KP6, false },
		{ Input_KeyCode::KP7, false },
		{ Input_KeyCode::KP8, false },
		{ Input_KeyCode::KP9, false },
		{ Input_KeyCode::KPDecimal, false },
		{ Input_KeyCode::KPDivide, false },
		{ Input_KeyCode::KPMultiply, false },
		{ Input_KeyCode::KPSubtract, false },
		{ Input_KeyCode::KPAdd, false },
		{ Input_KeyCode::KPEnter, false }
	};


	/*------------------------------------------------------------------------------------------------------------------------------
	GLFW to input mouse code map
	------------------------------------------------------------------------------------------------------------------------------*/
	std::unordered_map<int, Input_MouseCode> Input::GLFWtoInputMouse{
		{ GLFW_MOUSE_BUTTON_1, Input_MouseCode::Mouse_Left },
		{ GLFW_MOUSE_BUTTON_2, Input_MouseCode::Mouse_Right },
		{ GLFW_MOUSE_BUTTON_3, Input_MouseCode::Mouse_Middle },
		{ GLFW_MOUSE_BUTTON_5, Input_MouseCode::Mouse_LeftSide_Front },
		{ GLFW_MOUSE_BUTTON_4, Input_MouseCode::Mouse_LeftSide_Back }
	};

	/*------------------------------------------------------------------------------------------------------------------------------
	Input mouse to bool map
	------------------------------------------------------------------------------------------------------------------------------*/
	std::unordered_map<Input_MouseCode, bool> Input::InputMouseStatus{
		{ Input_MouseCode::Mouse_Left, false },
		{ Input_MouseCode::Mouse_Right, false },
		{ Input_MouseCode::Mouse_Middle, false },
		{ Input_MouseCode::Mouse_LeftSide_Front, false },
		{ Input_MouseCode::Mouse_LeftSide_Back, false }
	};

	bool Input::IsKeyPressed(Input_KeyCode keyCode) {
		return InputKeyStatus[keyCode];
	}

	bool Input::IsMousePressed(Input_MouseCode button) {
		return InputMouseStatus[button];
	}

	void Input::SetKeyStatus(int key, bool status) {
		InputKeyStatus[GLFWtoInputKey[key]] = status;
	}

	void Input::SetMouseStatus(int button, bool status) {
		InputMouseStatus[GLFWtoInputMouse[button]] = status;
	}

	Input_KeyCode Input::GetKeyCode(int key) {
		return GLFWtoInputKey[key];
	}

	Input_MouseCode Input::GetMouseCode(int button) {
		return GLFWtoInputMouse[button];
	}

}