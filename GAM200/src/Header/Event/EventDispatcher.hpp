#ifndef EVENT_DISPATCHER_H
#define EVENT_DISPATCHER_H

#include "Event.hpp" //event types
#include "KeyEvent.hpp" //event types
#include "MouseEvent.hpp" //event types
#include "WindowEvent.hpp" //event types

//Polymorphic queue (store Event*)
//Make singleton
class EventDispatcher {
public:
	EventDispatcher(Event& event) : m_event(event) {}

	template <typename T>
	void Dispatch(std::function<bool(T&)> eventFunction) {
		m_event.handled = eventFunction(*(T*)&m_event);
	}
private:
	Event& m_event;
};

#endif