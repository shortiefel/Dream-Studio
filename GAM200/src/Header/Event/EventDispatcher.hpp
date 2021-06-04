#ifndef EVENT_DISPATCHER_H
#define EVENT_DISPATCHER_H

#include "../pch.hpp"
#include "Event.hpp" //event types
#include "KeyEvent.hpp" //event types
#include "MouseEvent.hpp" //event types
#include "WindowEvent.hpp" //event types

//Currently is each instance has an event and is resolved immediately
//End goal: polymorphic queue that goes through events at the end of the game loop
//Require: Memory manager to create new event so that it can last one frame (single frame memory manager)
//(currently on hold) Polymorphic queue (store Event*)
//(currently on hold) Make singleton
class EventDispatcher {
public:
	EventDispatcher(Event& event) : m_event(event) {}
	
	template <typename T>
	void Dispatch(std::function<bool(T&)> eventFunction) {
		//m_event.handled = 
		eventFunction(*(T*)&m_event);
	}
	/*EventDispatcher() {}
	EventDispatcher(Event* event) {
		v_event.push_back(event);
	}
	
	void Dispatch() {
		for (std::vector<Event*>::iterator i = v_event.begin(); i != v_event.end(); ++i) {
			std::cout << v_event.size() << " " << (*i)->Details() << "\n";
		}
	}*/

private:
	Event& m_event;
	//std::vector<Event*> v_event;
};

#endif