/* Start Header**********************************************************************************/
/*
@file    UtilityEvent.cpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    28/08/2021
\brief
This file contain the UtilityEvent definition


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/


#include "Engine/Header/Event/UtilityEvent.hpp"

namespace Engine {
	
	/*-------------------------------------------------------------------------------------------------
	Save event
	-------------------------------------------------------------------------------------------------*/
	std::vector<SaveEventFP> SaveEvent::registeredFunctions;

	EventType SaveEvent::GetEventType() const {
		return EventType::SAVING;
	}
	std::string SaveEvent::Details() const {
		return "Program Saving";
	}

	Call_and_Register_Definition(SaveEvent, SaveEventFP);
}