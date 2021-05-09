#include "PhysicSystem.hpp"
#include "Physic.hpp"

//Static--------------------------------------------------------
PhysicSystem* PhysicSystem::s_instance = 0;

void PhysicSystem::Create() { s_instance = new PhysicSystem(); }
PhysicSystem* PhysicSystem::Get() { return s_instance; }
void PhysicSystem::Destroy() { delete s_instance; }
//---------------------------------------------------------------

void PhysicSystem::Update() {
	//Apply gravity

	//For all entities in PhysicSystem
	for (auto const& entity : mEntities) {
		//Check for isColliding (Check collision type to polymorphically change object)

		/*
		Get component for collider
		if object is box then cast to box
		if (!isColliding (obj1, obj2)) {

		}
		
		else if (obj1.isTrigger || obj2.isTrigger) {
			
		}

		//else resolve collision by pushing object out
		*/


	}
}

	