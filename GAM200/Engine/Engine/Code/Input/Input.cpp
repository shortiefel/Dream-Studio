/* Start Header**********************************************************************************/
/*
@file    Input.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu			100%
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

#define MOUSE_CHECK_UPDATE(mouse)	if (InputMouseStatus[mouse]== InputType::PRESS) {\
										InputMouseStatus[mouse] = InputType::REPEAT;\
									}\
									else  if (InputMouseStatus[mouse] == InputType::RELEASE) {\
										InputMouseStatus[mouse] = InputType::NONE;\
									}

namespace Engine {
	Math::vec2 Input::mousePosition;
	//Math::vec2 Input::mouseScroll;

	bool keyChange = false;

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
	std::unordered_map<Input_KeyCode, InputType> Input::InputKeyStatus{
		{ Input_KeyCode::T0, InputType::RELEASE },
		{ Input_KeyCode::T1, InputType::RELEASE },
		{ Input_KeyCode::T2, InputType::RELEASE },
		{ Input_KeyCode::T3, InputType::RELEASE },
		{ Input_KeyCode::T4, InputType::RELEASE },
		{ Input_KeyCode::T5, InputType::RELEASE },
		{ Input_KeyCode::T6, InputType::RELEASE },
		{ Input_KeyCode::T7, InputType::RELEASE },
		{ Input_KeyCode::T8, InputType::RELEASE },
		{ Input_KeyCode::T9, InputType::RELEASE },

		{ Input_KeyCode::A, InputType::RELEASE },
		{ Input_KeyCode::B, InputType::RELEASE },
		{ Input_KeyCode::C, InputType::RELEASE },
		{ Input_KeyCode::D, InputType::RELEASE },
		{ Input_KeyCode::E, InputType::RELEASE },
		{ Input_KeyCode::F, InputType::RELEASE },
		{ Input_KeyCode::G, InputType::RELEASE },
		{ Input_KeyCode::H, InputType::RELEASE },
		{ Input_KeyCode::I, InputType::RELEASE },
		{ Input_KeyCode::J, InputType::RELEASE },
		{ Input_KeyCode::K, InputType::RELEASE },
		{ Input_KeyCode::L, InputType::RELEASE },
		{ Input_KeyCode::M, InputType::RELEASE },
		{ Input_KeyCode::N, InputType::RELEASE },
		{ Input_KeyCode::O, InputType::RELEASE },
		{ Input_KeyCode::P, InputType::RELEASE },
		{ Input_KeyCode::Q, InputType::RELEASE },
		{ Input_KeyCode::R, InputType::RELEASE },
		{ Input_KeyCode::S, InputType::RELEASE },
		{ Input_KeyCode::T, InputType::RELEASE },
		{ Input_KeyCode::U, InputType::RELEASE },
		{ Input_KeyCode::V, InputType::RELEASE },
		{ Input_KeyCode::W, InputType::RELEASE },
		{ Input_KeyCode::X, InputType::RELEASE },
		{ Input_KeyCode::Y, InputType::RELEASE },
		{ Input_KeyCode::Z, InputType::RELEASE },

		//Function keys
		{ Input_KeyCode::F1, InputType::RELEASE },
		{ Input_KeyCode::F2, InputType::RELEASE },
		{ Input_KeyCode::F3, InputType::RELEASE },
		{ Input_KeyCode::F4, InputType::RELEASE },
		{ Input_KeyCode::F5, InputType::RELEASE },
		{ Input_KeyCode::F6, InputType::RELEASE },
		{ Input_KeyCode::F7, InputType::RELEASE },
		{ Input_KeyCode::F8, InputType::RELEASE },
		{ Input_KeyCode::F9, InputType::RELEASE },
		{ Input_KeyCode::F10, InputType::RELEASE },
		{ Input_KeyCode::F11, InputType::RELEASE },
		{ Input_KeyCode::F12, InputType::RELEASE },
		{ Input_KeyCode::F13, InputType::RELEASE },
		{ Input_KeyCode::F14, InputType::RELEASE },
		{ Input_KeyCode::F15, InputType::RELEASE },
		{ Input_KeyCode::F16, InputType::RELEASE },
		{ Input_KeyCode::F17, InputType::RELEASE },
		{ Input_KeyCode::F18, InputType::RELEASE },
		{ Input_KeyCode::F19, InputType::RELEASE },
		{ Input_KeyCode::F20, InputType::RELEASE },
		{ Input_KeyCode::F21, InputType::RELEASE },
		{ Input_KeyCode::F22, InputType::RELEASE },
		{ Input_KeyCode::F23, InputType::RELEASE },
		{ Input_KeyCode::F24, InputType::RELEASE },

		//Left side
		{ Input_KeyCode::Escape, InputType::RELEASE },
		{ Input_KeyCode::GraveAccent, InputType::RELEASE }, //` and ~ (Tilde)
		{ Input_KeyCode::Tab, InputType::RELEASE },
		{ Input_KeyCode::CapsLock, InputType::RELEASE },

		{ Input_KeyCode::Shift, InputType::RELEASE },
		{ Input_KeyCode::Control, InputType::RELEASE },
		{ Input_KeyCode::Alt, InputType::RELEASE },

		{ Input_KeyCode::Space, InputType::RELEASE },

		//Right side
		{ Input_KeyCode::Minus, InputType::RELEASE },
		{ Input_KeyCode::Equal, InputType::RELEASE },
		{ Input_KeyCode::Backspace, InputType::RELEASE },

		{ Input_KeyCode::LeftBracket, InputType::RELEASE },
		{ Input_KeyCode::RightBracket, InputType::RELEASE },
		{ Input_KeyCode::BackSlash, InputType::RELEASE }, // \

		{ Input_KeyCode::Semicolon, InputType::RELEASE },
		{ Input_KeyCode::Apostrophe, InputType::RELEASE },
		{ Input_KeyCode::Enter, InputType::RELEASE },

		{ Input_KeyCode::Comma, InputType::RELEASE },
		{ Input_KeyCode::Period, InputType::RELEASE },
		{ Input_KeyCode::FrontSlash, InputType::RELEASE }, /* / */


		{ Input_KeyCode::PrintScreen, InputType::RELEASE },
		{ Input_KeyCode::ScrollLock, InputType::RELEASE },
		{ Input_KeyCode::Pause, InputType::RELEASE },

		{ Input_KeyCode::Insert, InputType::RELEASE },
		{ Input_KeyCode::Delete, InputType::RELEASE },
		{ Input_KeyCode::Home, InputType::RELEASE },
		{ Input_KeyCode::End, InputType::RELEASE },
		{ Input_KeyCode::PageUp, InputType::RELEASE },
		{ Input_KeyCode::PageDown, InputType::RELEASE },

		//Arrow Keys
		{ Input_KeyCode::Left, InputType::RELEASE },
		{ Input_KeyCode::Right, InputType::RELEASE },
		{ Input_KeyCode::Up, InputType::RELEASE },
		{ Input_KeyCode::Down, InputType::RELEASE },

		//Keypad
		{ Input_KeyCode::NumLock, InputType::RELEASE },
		{ Input_KeyCode::KP0, InputType::RELEASE },
		{ Input_KeyCode::KP1, InputType::RELEASE },
		{ Input_KeyCode::KP2, InputType::RELEASE },
		{ Input_KeyCode::KP3, InputType::RELEASE },
		{ Input_KeyCode::KP4, InputType::RELEASE },
		{ Input_KeyCode::KP5, InputType::RELEASE },
		{ Input_KeyCode::KP6, InputType::RELEASE },
		{ Input_KeyCode::KP7, InputType::RELEASE },
		{ Input_KeyCode::KP8, InputType::RELEASE },
		{ Input_KeyCode::KP9, InputType::RELEASE },
		{ Input_KeyCode::KPDecimal, InputType::RELEASE },
		{ Input_KeyCode::KPDivide, InputType::RELEASE },
		{ Input_KeyCode::KPMultiply, InputType::RELEASE },
		{ Input_KeyCode::KPSubtract, InputType::RELEASE },
		{ Input_KeyCode::KPAdd, InputType::RELEASE },
		{ Input_KeyCode::KPEnter, InputType::RELEASE }
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
	std::unordered_map<Input_MouseCode, InputType> Input::InputMouseStatus{
		{ Input_MouseCode::Mouse_Left, InputType::RELEASE },
		{ Input_MouseCode::Mouse_Right, InputType::RELEASE },
		{ Input_MouseCode::Mouse_Middle, InputType::RELEASE },
		{ Input_MouseCode::Mouse_LeftSide_Front, InputType::RELEASE },
		{ Input_MouseCode::Mouse_LeftSide_Back, InputType::RELEASE }
	};

	bool Input::IsKeyPressed(Input_KeyCode keyCode) {
		return (InputKeyStatus[keyCode] == InputType::PRESS);
	}

	bool Input::IsKeyHold(Input_KeyCode keyCode) {
		InputType tt = InputKeyStatus[keyCode];
		return (tt == InputType::PRESS) || (tt == InputType::REPEAT);
	}		

	void Input::UpdateMouseStatus() {
		MOUSE_CHECK_UPDATE(Input_MouseCode::Mouse_Left);
		MOUSE_CHECK_UPDATE(Input_MouseCode::Mouse_Right);
		MOUSE_CHECK_UPDATE(Input_MouseCode::Mouse_Middle);
		MOUSE_CHECK_UPDATE(Input_MouseCode::Mouse_LeftSide_Front);
		MOUSE_CHECK_UPDATE(Input_MouseCode::Mouse_LeftSide_Back);

		if (keyChange) {
			keyChange = false;

			for (auto& [name, stat] : InputKeyStatus) {
				if (stat == InputType::PRESS) stat = InputType::REPEAT;
			}
		}
	}

	bool Input::IsMousePressed(Input_MouseCode button) {
		return (InputMouseStatus[button] == InputType::PRESS);
	}

	bool Input::IsMouseHold(Input_MouseCode button) {
		InputType tt = InputMouseStatus[button];
		return (tt == InputType::PRESS) || (tt == InputType::REPEAT);
	}

	bool Input::IsMouseReleased(Input_MouseCode button) {
		return InputMouseStatus[button] == InputType::RELEASE;
	}

	void Input::SetKeyStatus(int key, InputType status) {
		if (status == InputType::PRESS) keyChange = true;
		InputKeyStatus[GLFWtoInputKey[key]] = status;
	}

	void Input::SetMouseStatus(int button, InputType status) {

		InputMouseStatus[GLFWtoInputMouse[button]] = status;
	}

	/*void Input::SetMouseScroll(float xScroll, float yScroll) {
		mouseScroll = Math::vec2 { xScroll, yScroll };
	}

	Math::vec2 Input::GetMouseScroll() {
		return mouseScroll;
	}*/

	Input_KeyCode Input::GetKeyCode(int key) {
		return GLFWtoInputKey[key];
	}

	Input_MouseCode Input::GetMouseCode(int button) {
		return GLFWtoInputMouse[button];
	}

	void Input::SetMousePosition(Math::vec2 pos) {
		mousePosition = pos;
	}
	Math::vec2 Input::GetMousePosition() {
		return mousePosition;
	}

}