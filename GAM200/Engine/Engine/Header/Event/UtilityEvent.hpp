/* Start Header**********************************************************************************/
/*
@file    UtilityEvent.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    28/08/2021
\brief
This file contain the UtilityEvent declaration


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef UTILITY_EVENT_HPP
#define UTILITY_EVENT_HPP

#include "Engine/Header/Event/Event.hpp" //Event
#include "Engine/Header/pch.hpp"

namespace Engine {

	/*-------------------------------------------------------------------------------------------------
	Save event
	-------------------------------------------------------------------------------------------------*/
	class SaveEvent;
	typedef bool (*SaveEventFP)(const SaveEvent&);

	class SaveEvent : public Event {
	public:
		virtual EventType GetEventType() const override;
		virtual std::string Details() const override;

		virtual void CallRegisteredFunctions() override;
		static void RegisterFunction(SaveEventFP func);
	private:
		static std::vector<SaveEventFP> registeredFunctions;
	};


	/*-------------------------------------------------------------------------------------------------
	State event - Play/Stop state
	-------------------------------------------------------------------------------------------------*/
	class StateEvent;
	typedef bool (*StateEventFP)(const StateEvent&);
	
	class StateEvent : public Event {
	public:
		virtual EventType GetEventType() const override;
		virtual std::string Details() const override;

		virtual void CallRegisteredFunctions() override;
		static void RegisterFunction(StateEventFP func);
	private:
		static std::vector<StateEventFP> registeredFunctions;
	};

}

#endif