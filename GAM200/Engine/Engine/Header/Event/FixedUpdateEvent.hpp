/* Start Header**********************************************************************************/
/*
@file    FixedUpdateEvent.hpp
@authors	Ow Jian Wen	jianwen.o@digipen.edu		100%
@date    08/11/2021
\brief
#include "Engine/Header/Event/FixedUpdateEvent.hpp"
This file contain the FixedUpdate declaration


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef FIXED_UPDATE_EVENT_H
#define FIXED_UPDATE_EVENT_H

#include "Engine/Header/Event/Event.hpp" //Event

namespace Engine {
	class FixedUpdateEvent;
	typedef bool (*FixedUpdateFP)(const FixedUpdateEvent&);

	class FixedUpdateEvent : public Event {
	public:
		FixedUpdateEvent() {}

		virtual EventType GetEventType() const override;
		virtual std::string Details() const override;

		virtual void CallRegisteredFunctions() override;
		static void RegisterFunction(FixedUpdateFP func);

	private:
		static std::vector<FixedUpdateFP> registeredFunctions;
	};

}

#endif