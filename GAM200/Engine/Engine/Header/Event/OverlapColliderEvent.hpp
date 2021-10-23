/* Start Header**********************************************************************************/
/*
@file    OverlapColliderEvent.hpp
@authors	Goh See Yong Denise		g.seeyongdenise@digipen.edu
@date    28/08/2021
\brief
This file contain the OverlapEvent declaration

OnCollisionEnter
OnCollisionStay
OnCollisionExit
OnTriggerEnter
OnTriggerStay
OnTriggerExit

OnMouseEnter
OnMouseOver
OnMouseExit


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef OVERLAP_COLLIDER_EVENT_HPP
#define OVERLAP_COLLIDER_EVENT_HPP

#include "Engine/Header/Event/Event.hpp" //Event
#include "Engine/Header/Script/MonoFunctionType.hpp" //MonoFunctionType
#include "Engine/Header/pch.hpp"

namespace Engine {

	/*-------------------------------------------------------------------------------------------------
	OverlapCollider event
	-------------------------------------------------------------------------------------------------*/
	class OverlapColliderEvent;
	typedef bool (*OverlapColliderEventFP)(const OverlapColliderEvent&);

	class OverlapColliderEvent : public Event {
	public:
		virtual EventType GetEventType() const override;
		virtual std::string Details() const override;

		virtual void CallRegisteredFunctions() override;
		static void RegisterFunction(OverlapColliderEventFP func);

		OverlapColliderEvent(std::uint32_t _ent1, std::uint32_t _ent2, MonoFunctionType _type);

		std::uint32_t self, other;
		MonoFunctionType type;
	private:
		static std::vector<OverlapColliderEventFP> registeredFunctions;
	};

	/*-------------------------------------------------------------------------------------------------
	MouseOverlapCollider event
	-------------------------------------------------------------------------------------------------*/
	class MouseOverlapColliderEvent;
	typedef bool (*MouseOverlapColliderEventFP)(const MouseOverlapColliderEvent&);

	class MouseOverlapColliderEvent : public Event {
	public:
		virtual EventType GetEventType() const override;
		virtual std::string Details() const override;

		virtual void CallRegisteredFunctions() override;
		static void RegisterFunction(MouseOverlapColliderEventFP func);

		MouseOverlapColliderEvent(std::uint32_t _ent1, MonoFunctionType _type);

		std::uint32_t other;
		MonoFunctionType type;
	private:
		static std::vector<MouseOverlapColliderEventFP> registeredFunctions;
	};

}

#endif