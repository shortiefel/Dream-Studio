/* Start Header**********************************************************************************/
/*
@file    KeyEvent.cpp
@authors	Goh See Yong Denise		g.seeyongdenise@digipen.edu		100%
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
#include "Engine/Header/Debug Tools/Profiler.hpp"

namespace Engine {
	std::vector<KeyPressedFP> KeyPressedEvent::registeredFunctions;
	std::vector<KeyReleasedFP> KeyReleasedEvent::registeredFunctions;

	/*-------------------------------------------------------------------------------------------------
	Key event
	-------------------------------------------------------------------------------------------------*/
	Input_KeyCode KeyEvent::GetKeyCode() const { 
		PROFILER_START("Event");
		return keyCode; 
	}

	KeyEvent::KeyEvent(Input_KeyCode keycode) : keyCode{ keycode } {
		PROFILER_START("Event");
	}


	/*-------------------------------------------------------------------------------------------------
	Key pressed event
	-------------------------------------------------------------------------------------------------*/
	KeyPressedEvent::KeyPressedEvent(Input_KeyCode keycode, bool repeat) :
		KeyEvent(keycode), keyRepeat{ repeat } {
		PROFILER_START("Event");
	}

	EventType KeyPressedEvent::GetEventType() const {
		PROFILER_START("Event");
		return EventType::KEY_PRESSED;
	}
	std::string KeyPressedEvent::Details() const {
		PROFILER_START("Event");
		std::string tem{ "Key Pressed " };
		tem += keyRepeat ? "(Hold)" : "(Press)";
		return tem;
	}

	Call_and_Register_Definition(KeyPressedEvent, KeyPressedFP);


	/*-------------------------------------------------------------------------------------------------
	Key released event
	-------------------------------------------------------------------------------------------------*/
	KeyReleasedEvent::KeyReleasedEvent(Input_KeyCode keycode) :
		KeyEvent(keycode) {
		PROFILER_START("Event");
	}

	EventType KeyReleasedEvent::GetEventType() const {
		PROFILER_START("Event");
		return EventType::KEY_RELEASED;
	}

	std::string KeyReleasedEvent::Details() const {
		PROFILER_START("Event");
		return std::string{ "Key Released" };
	}

	Call_and_Register_Definition(KeyReleasedEvent, KeyReleasedFP);
}