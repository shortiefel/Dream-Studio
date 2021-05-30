#ifndef MOUSE_EVENT_H
#define MOUSE_EVENT_H

#include "Event.hpp"
#include "../Math/VectorAll.hpp"

//MOUSE_BUTTON_PRESSED, MOUSE_BUTTON_RELEASED, 
//MOUSE_MOVED, MOUSE_SCROLLED
class MousePressedEvent : public Event {
public:
	MousePressedEvent(int b) :
		button{ b } {}

	virtual EventType GetEventType() const override {
		return EventType::MOUSE_BUTTON_PRESSED;
	}

	virtual std::string Details() const override {
		std::string tem{ "Mouse Pressed: " };
		switch (button) {
		case GLFW_MOUSE_BUTTON_LEFT:
			tem += "Left";
			break;
		case GLFW_MOUSE_BUTTON_RIGHT:
			tem += "Right";
			break;
		case GLFW_MOUSE_BUTTON_MIDDLE:
			tem += "Middle";
			break;
		}
		return tem;
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

	virtual std::string Details() const override {
		return std::string{  "Mouse Released" };
	}

private:
	int button;
};

class MouseMoveEvent : public Event {
public:
	MouseMoveEvent(float xp, float yp) :
		pos{ xp, yp } {}

	inline MathD::Vec2 GetPos() const { return pos; }

	virtual EventType GetEventType() const override {
		return EventType::MOUSE_MOVE;
	}

	virtual std::string Details() const override {
		return std::string{ "Mouse Moved: " + std::to_string(pos.x) + ", " + std::to_string(pos.y) };
	}

private:
	MathD::Vec2 pos;
};

class MouseScrolledEvent : public Event {
public:
	MouseScrolledEvent(float x, float y) :
		scrollOffset{ x,y } {}

	virtual EventType GetEventType() const override {
		return EventType::MOUSE_SCROLLED;
	}

	virtual std::string Details() const override {
		return std::string{ "Mouse Scrolled: " + std::to_string(scrollOffset.x) + ", " + std::to_string(scrollOffset.y) };
	}

private:
	MathD::Vec2 scrollOffset;
};

#endif