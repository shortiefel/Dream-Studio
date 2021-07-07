/* Start Header**********************************************************************************/
/*
@file    KeyEvent.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    26/05/2021
\brief
This file contain the KeyEvent declaration


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef KEY_EVENT_H
#define KEY_EVENT_H

#include "Event/Event.hpp" //Event

//KEY_PRESSED, KEY_RELEASED
class KeyEvent : public Event {
public:
	int GetKeyCode() const { return keyCode; }
protected:
	KeyEvent(int keycode) : keyCode{ keycode } {}
	int keyCode;
};

class KeyPressedEvent : public KeyEvent {
public:
	KeyPressedEvent (int keycode, bool repeat) :
		KeyEvent(keycode), keyRepeat{ repeat } {}

	virtual EventType GetEventType() const override {
		return EventType::KEY_PRESSED;
	}
	virtual std::string Details() const override {
		std::string tem{ "Key Pressed "  };
		tem += keyRepeat ? "(Hold)" : "(Press)";
		return tem;
	}

private:
	bool keyRepeat = false;
};

class KeyReleasedEvent : public KeyEvent {
public:
	KeyReleasedEvent(int keycode) :
		KeyEvent(keycode) {}

	virtual EventType GetEventType() const override {
		return EventType::KEY_RELEASED;
	}

	virtual std::string Details() const override {
		return std::string{ "Key Released" };
	}
};


#endif