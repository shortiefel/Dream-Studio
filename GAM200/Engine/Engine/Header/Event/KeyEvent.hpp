/* Start Header**********************************************************************************/
/*
@file    KeyEvent.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
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

namespace Engine {
	//KEY_PRESSED, KEY_RELEASED
	/*-------------------------------------------------------------------------------------------------
	Key event
	-------------------------------------------------------------------------------------------------*/
	class KeyEvent : public Event {
	public:
		//Get the key code of pressed/released key
		int GetKeyCode() const;
	protected:
		KeyEvent(int keycode);
		int keyCode;
	};


	/*-------------------------------------------------------------------------------------------------
	Key pressed event
	-------------------------------------------------------------------------------------------------*/
	class KeyPressedEvent;
	typedef bool (*KeyPressFP)(const KeyPressedEvent&);

	class KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(int keycode, bool repeat);
		virtual EventType GetEventType() const override;
		virtual std::string Details() const override;

		virtual void CallRegisteredFunctions() override;
		static void RegisterFunction(KeyPressFP func);

	private:
		bool keyRepeat = false;
		static std::vector<KeyPressFP> registeredFunctions;
	};


	/*-------------------------------------------------------------------------------------------------
	Key released event
	-------------------------------------------------------------------------------------------------*/
	class KeyReleasedEvent;
	typedef bool (*KeyReleaseFP)(const KeyReleasedEvent&);

	class KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(int keycode);
		virtual EventType GetEventType() const override;
		virtual std::string Details() const override;

		virtual void CallRegisteredFunctions() override;
		static void RegisterFunction(KeyReleaseFP func);
	private:
		static std::vector<KeyReleaseFP> registeredFunctions;
	};
}

#endif