/* Start Header**********************************************************************************/
/*
@file    FixedUpdateEvent.cpp
@authors	Ow Jian Wen	jianwen.o@digipen.edu		100%
@date    08/11/2021
\brief
#include "Engine/Header/Event/FixedUpdateEvent.hpp"
This file contain the FixedUpdate definition


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Event/FixedUpdateEvent.hpp"

namespace Engine {
	std::vector<FixedUpdateFP> FixedUpdateEvent::registeredFunctions;

	/*-------------------------------------------------------------------------------------------------
	Fixed Update event
	-------------------------------------------------------------------------------------------------*/
	EventType FixedUpdateEvent::GetEventType() const {
		PROFILER_START("Event");
		return EventType::Fixed_Update;
	}

	std::string FixedUpdateEvent::Details() const {
		PROFILER_START("Event");
		return std::string{ "Fixed Update" };
	}

	Call_and_Register_Definition(FixedUpdateEvent, FixedUpdateFP);
}
