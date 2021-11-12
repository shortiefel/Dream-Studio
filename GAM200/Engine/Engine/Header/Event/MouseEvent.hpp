/* Start Header**********************************************************************************/
/*
@file    MouseEvent.hpp
@authors	Goh See Yong Denise		g.seeyongdenise@digipen.edu	100%
@date    26/05/2021
\brief
#include "Engine/Header/Event/MouseEvent.hpp"
This file contain the MouseEvent declaration
Refer to Event.hpp for more information


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef MOUSE_EVENT_H
#define MOUSE_EVENT_H

#include "Engine/Header/Event/Event.hpp"
#include "Engine/Header/pch.hpp"

#include "Engine/Header/Math/MathLib.hpp"

namespace Engine {
	//MOUSE_BUTTON_PRESSED, MOUSE_BUTTON_RELEASED, 
	//MOUSE_MOVED, MOUSE_SCROLLED

	/*-------------------------------------------------------------------------------------------------
	Mouse press event
	-------------------------------------------------------------------------------------------------*/
	class MousePressedEvent;
	typedef bool (*MousePressFP)(const MousePressedEvent&);

	class MousePressedEvent : public Event {
	public:
		MousePressedEvent(int b);
		virtual EventType GetEventType() const override;
		virtual std::string Details() const override;

		virtual void CallRegisteredFunctions() override;
		static void RegisterFunction(MousePressFP func);

	private:
		int button;
		static std::vector<MousePressFP> registeredFunctions;
	};


	/*-------------------------------------------------------------------------------------------------
	Mouse release
	-------------------------------------------------------------------------------------------------*/
	class MouseReleasedEvent;
	typedef bool (*MouseReleaseFP)(const MouseReleasedEvent&);

	class MouseReleasedEvent : public Event {
	public:
		MouseReleasedEvent(int b);
		virtual EventType GetEventType() const override;
		virtual std::string Details() const override;

		virtual void CallRegisteredFunctions() override;
		static void RegisterFunction(MouseReleaseFP func);

	private:
		int button;
		static std::vector<MouseReleaseFP> registeredFunctions;
	};


	/*-------------------------------------------------------------------------------------------------
	Mouse move event
	-------------------------------------------------------------------------------------------------*/
	class MouseMoveEvent;
	typedef bool (*MouseMoveFP)(const MouseMoveEvent&);

	class MouseMoveEvent : public Event {
	public:
		MouseMoveEvent(float xp, float yp, bool l, bool r, bool u, bool d);
		//Get mouse position when moved
		Math::vec2 GetPos() const;
		bool GetLeft() const;
		bool GetRight() const;
		bool GetUp() const;
		bool GetDown() const;
		virtual EventType GetEventType() const override;
		virtual std::string Details() const override;

		virtual void CallRegisteredFunctions() override;
		static void RegisterFunction(MouseMoveFP func);

	private:
		Math::vec2 pos;
		bool left, right, up, down;
		static std::vector<MouseMoveFP> registeredFunctions;
	};


	/*-------------------------------------------------------------------------------------------------
	Mouse scroll event
	-------------------------------------------------------------------------------------------------*/
	class MouseScrolledEvent;
	typedef bool (*MouseScrollFP)(const MouseScrolledEvent&);

	class MouseScrolledEvent : public Event {
	public:
		MouseScrolledEvent(float x, float y);
		Math::vec2 GetScroll() const;
		virtual EventType GetEventType() const override;
		virtual std::string Details() const override;

		virtual void CallRegisteredFunctions() override;
		static void RegisterFunction(MouseScrollFP func);

	private:
		Math::vec2 scrollOffset;
		static std::vector<MouseScrollFP> registeredFunctions;
	};
}

#endif