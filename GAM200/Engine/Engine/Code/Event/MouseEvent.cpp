/* Start Header**********************************************************************************/
/*
@file    MouseEvent.cpp
@authors	Goh See Yong Denise		g.seeyongdenise@digipen.edu
@date    27/07/2021
\brief
This file contain the MouseEvent definition


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Event/MouseEvent.hpp"
#include "Engine/Header/Debug Tools/Profiler.hpp"


namespace Engine {
	std::vector<MousePressFP> MousePressedEvent::registeredFunctions;
	std::vector<MouseReleaseFP> MouseReleasedEvent::registeredFunctions;
	std::vector<MouseMoveFP> MouseMoveEvent::registeredFunctions;
	std::vector<MouseScrollFP> MouseScrolledEvent::registeredFunctions;

	/*-------------------------------------------------------------------------------------------------
	Mouse press event
	-------------------------------------------------------------------------------------------------*/
	MousePressedEvent::MousePressedEvent(int b) :
		button{ b } {
		PROFILER_START("Event");
	}

	EventType MousePressedEvent::GetEventType() const {
		PROFILER_START("Event");
		return EventType::MOUSE_BUTTON_PRESSED;
	}

	std::string MousePressedEvent::Details() const {
		PROFILER_START("Event");
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

	Call_and_Register_Definition(MousePressedEvent, MousePressFP);


	/*-------------------------------------------------------------------------------------------------
	Mouse release
	-------------------------------------------------------------------------------------------------*/
	MouseReleasedEvent::MouseReleasedEvent(int b) :
		button{ b } {
		PROFILER_START("Event");
	}

	EventType MouseReleasedEvent::GetEventType() const {
		PROFILER_START("Event");
		return EventType::MOUSE_BUTTON_RELEASED;
	}

	std::string MouseReleasedEvent::Details() const {
		PROFILER_START("Event");
		return "Mouse Released";
	}

	Call_and_Register_Definition(MouseReleasedEvent, MouseReleaseFP);


	/*-------------------------------------------------------------------------------------------------
	Mouse move event
	-------------------------------------------------------------------------------------------------*/
	MouseMoveEvent::MouseMoveEvent(float xp, float yp) :
		pos{ xp, yp } {
		PROFILER_START("Event");
	}

	Math::vec2 MouseMoveEvent::GetPos() const { 
		PROFILER_START("Event");
		return pos; 
	}

	EventType MouseMoveEvent::GetEventType() const {
		PROFILER_START("Event");
		return EventType::MOUSE_MOVE;
	}

	std::string MouseMoveEvent::Details() const {
		PROFILER_START("Event");
		return std::string{ "Mouse Moved: " + std::to_string(pos.x) + ", " + std::to_string(pos.y) };
	}

	Call_and_Register_Definition(MouseMoveEvent, MouseMoveFP);


	/*-------------------------------------------------------------------------------------------------
	Mouse scroll event
	-------------------------------------------------------------------------------------------------*/
	MouseScrolledEvent::MouseScrolledEvent(float x, float y) :
		scrollOffset{ x,y } {
		PROFILER_START("Event");
	}

	Math::vec2 MouseScrolledEvent::GetScroll() const {
		PROFILER_START("Event");
		return scrollOffset;
	}

	EventType MouseScrolledEvent::GetEventType() const {
		PROFILER_START("Event");
		return EventType::MOUSE_SCROLLED;
	}

	std::string MouseScrolledEvent::Details() const {
		PROFILER_START("Event");
		return std::string{ "Mouse Scrolled: " + std::to_string(scrollOffset.x) + ", " + std::to_string(scrollOffset.y) };
	}

	Call_and_Register_Definition(MouseScrolledEvent, MouseScrollFP);
}