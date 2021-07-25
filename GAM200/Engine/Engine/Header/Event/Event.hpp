/* Start Header**********************************************************************************/
/*
@file    Event.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    26/05/2021
\brief
This file contain the Event declaration


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef EVENT_H
#define EVENT_H

#include <iostream> //operator<< overload

namespace Engine {
	enum class EventType {
		NONE = 0,
		WINDOW_CLOSE, WINDOW_RESIZE, WINDOW_MOVED,
		KEY_PRESSED, KEY_RELEASED,
		MOUSE_MOVE, MOUSE_BUTTON_PRESSED, MOUSE_BUTTON_RELEASED, MOUSE_SCROLLED
	};

	class Event {
	public:
		virtual EventType GetEventType() const {
			std::cout << "rip\n";
			return EventType::KEY_PRESSED;
		}
		virtual std::string Details() const = 0;

		virtual void CallRegisteredFunctions() {
			
		}

		friend std::ostream& operator<<(std::ostream& os, const Event& event) {
			os << event.Details();
			return os;
		}
	protected:
		bool handled = false;
	};
}

#endif