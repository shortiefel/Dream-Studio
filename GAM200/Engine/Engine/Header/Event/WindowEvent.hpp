/* Start Header**********************************************************************************/
/*
@file    WindowEvent.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    26/05/2021
\brief
This file contain the WindowEvent declaration


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef WINDOW_EVENT_H
#define WINDOW_EVENT_H

#include "Engine/Header/Event/Event.hpp" //Event
#include "Engine/Header/Math/Vector.hpp" //Vec2

namespace Engine {
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
}

#endif