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
#include "Engine/Header/pch.hpp"
#include "Engine/Header/Math/MathLib.hpp"

namespace Engine {
	class WindowCloseEvent;
	typedef bool (*WinCloseFP)(const WindowCloseEvent&);
	class WindowResizeEvent;
	typedef bool (*WinResizeFP)(const WindowResizeEvent&);

	//WINDOW_CLOSE, WINDOW_RESIZE, WINDOW_MOVED
	class WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() {}

		virtual EventType GetEventType() const override;
		virtual std::string Details() const override;

		virtual void CallRegisteredFunctions() override;
		static void RegisterFunction(WinCloseFP func);

	private:
		static std::vector<WinCloseFP> registeredFunctions;
	};

	class WindowResizeEvent : public Event {
	public:
		WindowResizeEvent(unsigned int w, unsigned int h);

		inline Math::uvec2 GetSize() const {
			return w_size;
		}

		virtual EventType GetEventType() const override;
		virtual std::string Details() const override;

		virtual void CallRegisteredFunctions() override;
		static void RegisterFunction(WinResizeFP func);

	private:
		Math::uvec2 w_size;
		static std::vector<WinResizeFP> registeredFunctions;
	};
}

#endif