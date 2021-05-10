#ifndef MOUSE_EVENT_H
#define MOUSE_EVENT_H

#include "Event.hpp"
#include "../Math/Vector2D.hpp"


//MOUSE_BUTTON_PRESSED, MOUSE_BUTTON_RELEASED, 
//MOUSE_MOVED, MOUSE_SCROLLED
class MousePressedEvent : public Event {
public:
	MousePressedEvent(int b) :
		button{ b } {}

	virtual EventType GetEventType() const override {
		return EventType::MOUSE_BUTTON_PRESSED;
	}

private:
	int button;
};

class MouseReleasedEvent : public Event {
public:
	MouseReleasedEvent(int b) :
		button{ b } {}

	virtual EventType GetEventType() const override {
		return EventType::MOUSE_BUTTON_RELEASED;
	}

private:
	int button;
};

class MouseMoveEvent : public Event {
public:
	MouseMoveEvent(float x, float y) :
		pos{ x,y } {}

	inline Vec2 GetPos() const { return pos; }

	virtual EventType GetEventType() const override {
		return EventType::MOUSE_MOVE;
	}

private:
	Vec2 pos;
};

class MouseScrolledEvent : public Event {
public:
	MouseScrolledEvent(float x, float y) :
		scrollOffset{ x,y } {}

	virtual EventType GetEventType() const override {
		return EventType::MOUSE_SCROLLED;
	}

private:
	Vec2 scrollOffset;
};

#endif