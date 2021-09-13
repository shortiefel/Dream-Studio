/* Start Header**********************************************************************************/
/*
@file    KeyEvent.cpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    27/07/2021
\brief
This file contain the KeyEvent definition


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Event/KeyEvent.hpp"

namespace Engine {
	std::vector<KeyPressedFP> KeyPressedEvent::registeredFunctions;
	std::vector<KeyReleasedFP> KeyReleasedEvent::registeredFunctions;

	/*-------------------------------------------------------------------------------------------------
	Key event
	-------------------------------------------------------------------------------------------------*/
	Input_KeyCode KeyEvent::GetKeyCode() const { return keyCode; }
	KeyEvent::KeyEvent(Input_KeyCode keycode) : keyCode{ keycode } {}


	/*-------------------------------------------------------------------------------------------------
	Key pressed event
	-------------------------------------------------------------------------------------------------*/
	KeyPressedEvent::KeyPressedEvent(Input_KeyCode keycode, bool repeat) :
		KeyEvent(keycode), keyRepeat{ repeat } {}

	EventType KeyPressedEvent::GetEventType() const {
		return EventType::KEY_PRESSED;
	}
	std::string KeyPressedEvent::Details() const {
		std::string tem{ "Key Pressed " };
		tem += keyRepeat ? "(Hold)" : "(Press)";
		return tem;
	}

	Call_and_Register_Definition(KeyPressedEvent, KeyPressedFP);


	/*-------------------------------------------------------------------------------------------------
	Key released event
	-------------------------------------------------------------------------------------------------*/
	KeyReleasedEvent::KeyReleasedEvent(Input_KeyCode keycode) :
		KeyEvent(keycode) {}

	EventType KeyReleasedEvent::GetEventType() const {
		return EventType::KEY_RELEASED;
	}

	std::string KeyReleasedEvent::Details() const {
		return std::string{ "Key Released" };
	}

	Call_and_Register_Definition(KeyReleasedEvent, KeyReleasedFP);
}