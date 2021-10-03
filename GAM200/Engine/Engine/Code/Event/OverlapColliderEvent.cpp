/* Start Header**********************************************************************************/
/*
@file    OverlapColliderEvent.cpp
@authors	Goh See Yong Denise		g.seeyongdenise@digipen.edu
@date    28/08/2021
\brief
This file contain the OverlapColliderEvent definition


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/


#include "Engine/Header/Event/OverlapColliderEvent.hpp"

namespace Engine {

	/*-------------------------------------------------------------------------------------------------
	OverlapCollider event
	-------------------------------------------------------------------------------------------------*/
	std::vector<OverlapColliderEventFP> OverlapColliderEvent::registeredFunctions;

	OverlapColliderEvent::OverlapColliderEvent(std::uint32_t _ent1, std::uint32_t _ent2, MonoFunctionType _type)
		: self{ _ent1 }, other{ _ent2 }, type{ _type } {}

	EventType OverlapColliderEvent::GetEventType() const {
		return EventType::OVERLAP_COLLIDER;
	}
	std::string OverlapColliderEvent::Details() const {
		return "Overlapping collider Detected";
	}

	Call_and_Register_Definition(OverlapColliderEvent, OverlapColliderEventFP);

}