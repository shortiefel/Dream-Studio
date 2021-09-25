/* Start Header**********************************************************************************/
/*
@file    OverlapColliderEvent.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    28/08/2021
\brief
This file contain the OverlapEvent declaration

OnCollisionEnter
OnCollisionStay
OnCollisionExit
OnTriggerEnter
OnTriggerStay
OnTriggerExit


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

		OverlapColliderEvent(unsigned int _ent1, unsigned int _ent2, MonoFunctionType _type);

		unsigned int self, other;
		MonoFunctionType type;
	private:
		static std::vector<OverlapColliderEventFP> registeredFunctions;
	};

}

#endif