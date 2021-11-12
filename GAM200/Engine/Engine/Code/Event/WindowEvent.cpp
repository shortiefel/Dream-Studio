/* Start Header**********************************************************************************/
/*
@file    WindowEvent.cpp
@authors	Goh See Yong Denise		g.seeyongdenise@digipen.edu		100%
@date    25/07/2021
\brief
This file contain the WindowEvent definition


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Event/WindowEvent.hpp"
#include "Engine/Header/Debug Tools/Profiler.hpp"

namespace Engine {
	std::vector<WinCloseFP> WindowCloseEvent::registeredFunctions;
	std::vector<WinResizeFP> WindowResizeEvent::registeredFunctions;

	/*-------------------------------------------------------------------------------------------------
	Window close event
	-------------------------------------------------------------------------------------------------*/
	EventType WindowCloseEvent::GetEventType() const {
		PROFILER_START("Event");
		return EventType::WINDOW_CLOSE;
	}

	std::string WindowCloseEvent::Details() const {
		PROFILER_START("Event");
		return std::string{ "Window Closed" };
	}

	Call_and_Register_Definition(WindowCloseEvent, WinCloseFP);


	/*-------------------------------------------------------------------------------------------------
	Window resize event
	-------------------------------------------------------------------------------------------------*/
	WindowResizeEvent::WindowResizeEvent(unsigned int w, unsigned int h) :
		w_size{ w, h } {
		PROFILER_START("Event");
	}

	EventType WindowResizeEvent::GetEventType() const {
		PROFILER_START("Event");
		return EventType::WINDOW_RESIZE;
	}

	std::string WindowResizeEvent::Details() const {
		PROFILER_START("Event");
		return std::string{ "Window Resized: " + std::to_string(w_size.x) + ", " + std::to_string(w_size.y) };
	}

	Call_and_Register_Definition(WindowResizeEvent, WinResizeFP);
}