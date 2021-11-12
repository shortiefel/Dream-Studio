/* Start Header**********************************************************************************/
/*
@file    EventDispatcher.cpp
@authors	Goh See Yong Denise		g.seeyongdenise@digipen.edu	1005
@date    27/07/2021
\brief
This file contain the Event dispatcher definition


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Debug tools/Logging.hpp"
#include "Engine/Header/Event/EventDispatcher.hpp"

namespace Engine {
	void EventDispatcher::SendEvent(Event& event) {
		PROFILER_START("Event");

		LOG_EVENT(event);
		event.CallRegisteredFunctions();
	}
}