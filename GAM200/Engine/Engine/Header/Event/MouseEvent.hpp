/* Start Header**********************************************************************************/
/*
@file    MouseEvent.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    26/05/2021
\brief
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
#include "Engine/Header/Math/Vector.hpp"
#include "Engine/Header/pch.hpp"

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
		MouseMoveEvent(float xp, float yp);
		//Get mouse position when moved
		MathD::Vec2 GetPos() const;
		virtual EventType GetEventType() const override;
		virtual std::string Details() const override;

		virtual void CallRegisteredFunctions() override;
		static void RegisterFunction(MouseMoveFP func);

	private:
		MathD::Vec2 pos;
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
		MathD::Vec2 GetScroll() const;
		virtual EventType GetEventType() const override;
		virtual std::string Details() const override;

		virtual void CallRegisteredFunctions() override;
		static void RegisterFunction(MouseScrollFP func);

	private:
		MathD::Vec2 scrollOffset;
		static std::vector<MouseScrollFP> registeredFunctions;
	};
}

#endif