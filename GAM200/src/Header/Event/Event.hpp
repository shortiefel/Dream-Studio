#ifndef EVENT_H
#define EVENT_H

#include <iostream>

enum class EventType {
	NONE = 0,
	WINDOW_CLOSE, WINDOW_RESIZE, WINDOW_MOVED,
	KEY_PRESSED, KEY_RELEASED,
	MOUSE_MOVE, MOUSE_BUTTON_PRESSED, MOUSE_BUTTON_RELEASED, MOUSE_SCROLLED
};

class Event {
public:
	virtual EventType GetEventType() const = 0;
	virtual std::string Details() const = 0;

	friend std::ostream& operator<<(std::ostream& os, const Event& event) {
		os << event.Details();
		return os;
	}
protected:
	bool handled = false;
};

#endif