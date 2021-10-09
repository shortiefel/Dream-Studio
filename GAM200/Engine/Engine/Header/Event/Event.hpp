/* Start Header**********************************************************************************/
/*
@file    Event.hpp
@authors	Goh See Yong Denise		g.seeyongdenise@digipen.edu
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
#include "Engine/Header/Debug Tools/Profiler.hpp"

//#define EventType_To_String(x) #x

//Definition for the CallRegisteredFunctions and RegisterFunction
//Functions would do the same thing but *this,
//functions from registeredFunctions and type of 
//function pointer would be different
//Note: Can be found in Event.hpp
#define Call_and_Register_Definition(xType, fp) \
	void xType::CallRegisteredFunctions() {\
		PROFILER_START("Event");\
		for (auto& func : registeredFunctions) {\
			if (func(*this)) {\
				this->handled = true;\
				break;\
			}\
		}\
	}\
\
	void xType::RegisterFunction(fp func) {\
		PROFILER_START("Event");\
		registeredFunctions.emplace_back(func);\
	}


namespace Engine {
	enum class EventType {
		NONE = 0,
		WINDOW_CLOSE, WINDOW_RESIZE, WINDOW_MOVED,
		KEY_PRESSED, KEY_RELEASED,
		MOUSE_MOVE, MOUSE_BUTTON_PRESSED, MOUSE_BUTTON_RELEASED, MOUSE_SCROLLED,
		OVERLAP_COLLIDER
	};

	class Event {
	public:
		//return variable of type EventType
		virtual EventType GetEventType() const = 0;
		//return string of EventType
		virtual std::string Details() const = 0;
		//Call all registered functions
		virtual void CallRegisteredFunctions() = 0;

		friend std::ostream& operator<<(std::ostream& os, const Event& event) {
			PROFILER_START("Event");
			os << event.Details();
			return os;
		}
	protected:
		bool handled = false;
	};
}

#endif