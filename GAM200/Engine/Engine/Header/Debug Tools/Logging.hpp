/* Start Header**********************************************************************************/
/*
@file    ScriptComponent.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    26/05/2021
\brief

Add this to use
#include "Engine/Header/Debug Tools/Logging.hpp"

This file allow text to be written to console and changing color of text to indicate type of message
Allow user to track all the instructions that are supposed to be done

How to Use:
include file Logging.hpp before any other files to prevent redefinition

Can display up to a total of 3 variable (different or same types)
E.g. A string variable or Event type (to display type of events)

Used for printing of normal information to check whether something works (Blue text)
LOG_INFO(...)

Used for printing of event information (Green text)
LOG_EVENT(...)

Used for printing of warnings (Purple text)
LOG_WARNING(...)

Used for printing of errors (Red text)
LOG_ERROR(...)

Used for printing of instance (Eg: application, manager) creation and destruction (Yellow text)
LOG_INSTANCE(...)

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef LOGGING_H
#define LOGGING_H

//if not debug mode all logging will not be shown
#ifdef _DEBUG

#include <Windows.h> //Setting console text color
#include <iostream> //ostream
#include <assert.h>

#include "Engine/Header/Event/Event.hpp" //checking of event types


//Since mouse moved gets triggered pretty much all the time, this is to prevent it from triggering if you do not need it
//1 to show and 0 to not show
#define SHOW_MOUSE_MOVED 0

enum class LogState {
	Info = 0,
	Event,
	Warning,
	Error,
	Instance
};

#define LOG_INFO(...)    Engine::Logging::AddLog(LogState::Info, __VA_ARGS__)
#define LOG_EVENT(...)   Engine::Logging::AddLog(LogState::Event, __VA_ARGS__)
#define LOG_WARNING(...) Engine::Logging::AddLog(LogState::Warning, __VA_ARGS__)
#define LOG_ERROR(...)   Engine::Logging::AddLog(LogState::Error, __VA_ARGS__)
#define LOG_INSTANCE(...)   Engine::Logging::AddLog(LogState::Instance, __VA_ARGS__)
#define LOG_ASSERT(t) assert(t)

namespace Engine {
	//EmptyClass is used to have default parameter for logging that can be ignored
	class EmptyClass {
		friend std::ostream& operator<< (std::ostream& os, const EmptyClass&) { return os; }
	};

	class Logging {
	public:
		template <typename T, typename Y = EmptyClass, typename U = EmptyClass>
		static void AddLog(LogState ls, const T& t1, const Y& t2 = EmptyClass(), const U& t3 = EmptyClass()) {
			if (CheckType(t1)) return;
			if (CheckType(t2)) return;
			if (CheckType(t3)) return;

			int col = 7;
			switch (ls) {
			case LogState::Info:
				col = 9;
				std::cout << "[Info] ";
				break;
			case LogState::Event:
				col = 10;
				std::cout << "[Event] ";
				break;
			case LogState::Warning:
				col = 13;
				std::cout << "[Warning] ";
				break;
			case LogState::Error:
				col = 4;
				std::cout << "[Error] ";
				break;
			case LogState::Instance:
				col = 14;
				std::cout << "[Instance] ";
				break;
			}


			/*switch (ls) {
			case LogState::Info:
				col = 9;
				break;
			case LogState::Keys:
				col = 10;
				break;
			case LogState::Warning:
				col = 13;
				break;
			case LogState::Error:
				col = 4;
				break;
			case LogState::Instance:
				col = 14;
				break;
			}*/

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), col);


			/*switch (ls) {
			case LogState::Info:
				std::cout << "[Info] ";
				break;
			case LogState::Keys:
				std::cout << "[Keys] ";
				break;
			case LogState::Warning:
				std::cout << "[Warning] ";
				break;
			case LogState::Error:
				std::cout << "[Error] ";
				break;
			case LogState::Instance:
				std::cout << "[Instance] ";
				break;
			}*/

			std::cout << t1 << " ";
			if (typeid(Y) != typeid (EmptyClass))
				std::cout << t2 << " ";
			if (typeid(U) != typeid (EmptyClass))
				std::cout << t3;
			std::cout << "\n";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}

		//Check type is used to check for Event type (to remove mouse move event from flooding the console)
		template <typename T>
		static bool CheckType(const T&) {
			return 0;
		}

		template <>
		static bool CheckType(const Event& tem) {
			if (!SHOW_MOUSE_MOVED && tem.GetEventType() == EventType::MOUSE_MOVE) return 1;
			return 0;
		}

	};
}

#else
//do {} while (0) to remove warnings
#define LOG_INFO(...)		do {} while (0)
#define LOG_EVENT(...)		do {} while (0)
#define LOG_WARNING(...)	do {} while (0)
#define LOG_ERROR(...)		do {} while (0)
#define LOG_INSTANCE(...)   do {} while (0)
#define LOG_ASSERT(t)		do {} while (0)

#endif



#endif
