//Example singleton for managers (e.g: Physic/Graphic manager)

#include "Singleton.hpp"
#include "pch.hpp"

Singleton* Singleton::s_instance = 0;

void Singleton::Create() {
	
	if (!s_instance) {
		s_instance = new Singleton();
		//logging 
	}
}

void Singleton::Destroy() {
	assert(s_instance);
	
	delete s_instance;
	//logging 
}

Singleton* Singleton::Get() {
	assert(s_instance);
	return s_instance;
}


