#ifndef EVENT_H
#define EVENT_H

enum class EventType {
	NONE = 0,
	WINDOW_CLOSE, WINDOW_RESIZE, WINDOW_MOVED,
	KEY_PRESSED, KEY_RELEASED,
	MOUSE_MOVE, MOUSE_BUTTON_PRESSED, MOUSE_BUTTON_RELEASED, MOUSE_SCROLLED
};

class Event {
public:
	virtual EventType GetEventType() const = 0;
protected:
	bool handled = false;
};



#endif