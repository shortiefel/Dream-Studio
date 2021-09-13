/* Start Header**********************************************************************************/
/*
@file    EventDispatcher.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    26/05/2021
\brief
This file contain the Event dispatcher declaration


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef EVENT_DISPATCHER_H
#define EVENT_DISPATCHER_H

#include "Engine/Header/pch.hpp"
#include "Engine/Header/Event/Event.hpp" //event types
#include "Engine/Header/Event/KeyEvent.hpp" //event types
#include "Engine/Header/Event/MouseEvent.hpp" //event types
#include "Engine/Header/Event/WindowEvent.hpp" //event types

namespace Engine {
	//Currently is each instance has an event and is resolved immediately
	//End goal: polymorphic queue that goes through events at the end of the game loop
	//Require: Memory manager to create new event so that it can last one frame (single frame memory manager)
	//(currently on hold) Polymorphic queue (store Event*)
	//(currently on hold) Make singleton
	class EventDispatcher {
	public:
		//EventDispatcher(Event& event) : m_event(event) {}

		//template <typename T>
		//void Dispatch(std::function<bool(T&)> eventFunction) {
		//	//m_event.handled = 
		//	eventFunction(*(T*)&m_event);
		//}
		/*EventDispatcher() {}
		EventDispatcher(Event* event) {
			v_event.push_back(event);
		}

		void Dispatch() {
			for (std::vector<Event*>::iterator i = v_event.begin(); i != v_event.end(); ++i) {
				std::cout << v_event.size() << " " << (*i)->Details() << "\n";
			}
		}*/

		static void SendEvent(Event& event);

	private:
		//Event& m_event;
		//std::vector<Event*> v_event;
	};
}

#endif