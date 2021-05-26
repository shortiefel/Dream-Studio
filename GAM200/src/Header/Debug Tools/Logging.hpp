//This file allow text to be written to console and changing color of text to indicate type of message
//Allow user to track all the instructions that are supposed to be done

//How to Use:
//include file Logging.hpp before any other files to prevent redefinition
/*
Can display up to a total of 3 variable (different or same types)
E.g. A string variable or Event type (to display type of events)

//Used for printing of normal information to check whether something works (Green text)
LOG_INFO(...) 

//Used for printing of debug information (White text)
LOG_DEBUG(...)

//Used for printing of warnings (Yellow text)
LOG_WARNING(...) 

//Used for printing of errors (Red text)
LOG_ERROR(...)
*/

#ifndef LOGGING_H
#define LOGGING_H



//if not debug mode all logging will not be shown
#ifdef _DEBUG

#include <Windows.h> //Setting console text color
#include <iostream> //ostream

#include "../Event/Event.hpp" //checking of event types

//Since mouse moved gets triggered pretty much all the time, this is to prevent it from triggering if you do not need it
//1 to show and 0 to not show
#define SHOW_MOUSE_MOVED 0

#define LOG_INFO(...)    Logging::AddLog(3, __VA_ARGS__)
#define LOG_DEBUG(...)   Logging::AddLog(2, __VA_ARGS__)
#define LOG_WARNING(...) Logging::AddLog(6, __VA_ARGS__)
#define LOG_ERROR(...)   Logging::AddLog(4, __VA_ARGS__)


//EmptyClass is used to have default parameter for logging that can be ignored
class EmptyClass {
	friend std::ostream& operator<< (std::ostream& os, const EmptyClass&) { return os; }
};

class Logging {
public:
	template <typename T, typename Y = EmptyClass, typename U = EmptyClass>
	static void AddLog(int col, const T& t1, const Y& t2 = EmptyClass(), const U& t3 = EmptyClass()) {
		if (CheckType(t1)) return;
		if (CheckType(t2)) return;
		if (CheckType(t3)) return;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), col);
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

#else

#define LOG_INFO(x) ; 
#define LOG_DEBUG(x) ; 
#define LOG_WARNING(x) ; 
#define LOG_ERROR(x) ;
#endif



#endif
