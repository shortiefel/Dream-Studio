#include "PhysicManager.hpp"
#include "Physic.hpp"


PhysicManager* PhysicManager::s_instance = 0;

void PhysicManager::Create() { s_instance = new PhysicManager(); }
PhysicManager* PhysicManager::Get() { return s_instance; }
void PhysicManager::Destroy() { delete s_instance; }


void PhysicManager::Run() {
	//Apply gravity

}

	