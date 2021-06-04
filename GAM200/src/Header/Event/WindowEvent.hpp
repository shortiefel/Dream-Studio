#ifndef WINDOW_EVENT_H
#define WINDOW_EVENT_H

#include "Event/Event.hpp" //Event
#include "Math/Vector.hpp" //Vec2

//WINDOW_CLOSE, WINDOW_RESIZE, WINDOW_MOVED
class WindowCloseEvent : public Event {
public:
	WindowCloseEvent() {}

	virtual EventType GetEventType() const override {
		return EventType::WINDOW_CLOSE;
	}

	virtual std::string Details() const override {
		return std::string{ "Window Closed" };
	}
};

class WindowResizeEvent : public Event {
public:
	WindowResizeEvent(unsigned int w, unsigned int h) :
		w_size{ w, h } {}

	inline MathD::uiVec2 GetSize() const {
		return w_size;
	}

	virtual EventType GetEventType() const override {
		return EventType::WINDOW_RESIZE;
	}

	virtual std::string Details() const override {
		return std::string{ "Window Resized: " + std::to_string(w_size.x) + ", " + std::to_string(w_size.y) };
	}

private:
	MathD::uiVec2 w_size;

};

#endif