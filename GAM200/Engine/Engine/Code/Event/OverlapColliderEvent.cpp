/* Start Header**********************************************************************************/
/*
@file    OverlapColliderEvent.cpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
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

	OverlapColliderEvent::OverlapColliderEvent(unsigned int ent1, unsigned int ent2, OverlapType otype)
		: self{ ent1 }, other{ ent2 }, type{ otype } {}

	EventType OverlapColliderEvent::GetEventType() const {
		return EventType::OVERLAP_COLLIDER;
	}
	std::string OverlapColliderEvent::Details() const {
		return "Overlapping collider Detected";
	}

	Call_and_Register_Definition(OverlapColliderEvent, OverlapColliderEventFP);

}