#ifndef EVENT_DISPATCHER_H
#define EVENT_DISPATCHER_H

#include "Event.hpp"
#include "KeyEvent.hpp"
#include "MouseEvent.hpp"
#include "WindowEvent.hpp"

//Polymorphic queue (store Event*)
//Make singleton
class EventDispatcher {
public:
	EventDispatcher(Event& event) : m_event(event) {}

	template <typename T>
	void Dispatch(std::function<bool(T&)> eventFunction) {
		eventFunction(*(T*)&m_event);
	}
private:
	Event& m_event;
};

#endif