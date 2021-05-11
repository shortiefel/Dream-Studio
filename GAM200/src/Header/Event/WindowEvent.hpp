#ifndef WINDOW_EVENT_H
#define WINDOW_EVENT_H

#include "Event.hpp"
#include "../Math/Vector2D.hpp"

//WINDOW_CLOSE, WINDOW_RESIZE, WINDOW_MOVED
class WindowCloseEvent : public Event {
public:
	WindowCloseEvent() {}

	virtual EventType GetEventType() const override {
		return EventType::WINDOW_CLOSE;
	}
};

class WindowResizeEvent : public Event {
public:
	WindowResizeEvent(unsigned int w, unsigned int h) :
		w_size{ w, h } {}

	inline uiVec2 GetSize() const {
		return w_size;
	}

	virtual EventType GetEventType() const override {
		return EventType::WINDOW_RESIZE;
	}

private:
	uiVec2 w_size;

};

#endif