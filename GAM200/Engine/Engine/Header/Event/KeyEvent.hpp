/* Start Header**********************************************************************************/
/*
@file    KeyEvent.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    26/05/2021
\brief
This file contain the KeyEvent declaration
Refer to Event.hpp for more information


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef KEY_EVENT_H
#define KEY_EVENT_H

#include "Engine/Header/Event/Event.hpp" //Event
#include "Engine/Header/pch.hpp"
#include "Engine/Header/Input/Input.hpp"

namespace Engine {
	//KEY_PRESSED, KEY_RELEASED
	/*-------------------------------------------------------------------------------------------------
	Key event
	-------------------------------------------------------------------------------------------------*/
	class KeyEvent : public Event {
	public:
		//Get the key code of pressed/released key
		Input_KeyCode GetKeyCode() const;
	protected:
		KeyEvent(Input_KeyCode keycode);
		Input_KeyCode keyCode;
	};


	/*-------------------------------------------------------------------------------------------------
	Key pressed event
	-------------------------------------------------------------------------------------------------*/
	class KeyPressedEvent;
	typedef bool (*KeyPressedFP)(const KeyPressedEvent&);

	class KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(Input_KeyCode keycode, bool repeat);
		virtual EventType GetEventType() const override;
		virtual std::string Details() const override;

		virtual void CallRegisteredFunctions() override;
		static void RegisterFunction(KeyPressedFP func);

	private:
		bool keyRepeat = false;
		static std::vector<KeyPressedFP> registeredFunctions;
	};


	/*-------------------------------------------------------------------------------------------------
	Key released event
	-------------------------------------------------------------------------------------------------*/
	class KeyReleasedEvent;
	typedef bool (*KeyReleasedFP)(const KeyReleasedEvent&);

	class KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(Input_KeyCode keycode);
		virtual EventType GetEventType() const override;
		virtual std::string Details() const override;

		virtual void CallRegisteredFunctions() override;
		static void RegisterFunction(KeyReleasedFP func);
	private:
		static std::vector<KeyReleasedFP> registeredFunctions;
	};
}

#endif