/*
This file has the function definition for class PhysicSystem
*/

#include "Debug Tools/Logging.hpp"
#include "System/PhysicSystem.hpp"
#include "Physic/Physic.hpp"


//Static--------------------------------------------------------
//PhysicSystem* PhysicSystem::s_instance = 0;
//PhysicSystem* PhysicSystem::Get() { return s_instance; }

//---------------------------------------------------------------
namespace PhysicImplementation {
	void PhysicSystem::Update(float dt) {


		//For all entities in PhysicSystem
		for (auto const& entity : mEntities) {
			//Apply gravity if rigidbody exist and rigidbody hasGravity
			//

			//Check for isColliding (Check collision type to polymorphically change object)


			////Get component for collider
			////if object is box then cast to box
			//if (!Physic::isColliding (obj1, obj2)) {

			//}
			//
			//else if (obj1.isTrigger || obj2.isTrigger) {
			//	
			//}

			//else resolve collision by pushing object out



		}
	}

	bool PhysicSystem::Create() {
		LOG_INSTANCE("Physic System created");
		//s_instance = new PhysicSystem();
		return true;
	}
	void PhysicSystem::Destroy() {
		LOG_INSTANCE("Physic System destroyed");
		//delete s_instance; 
	}

	PhysicSystem::~PhysicSystem() { Destroy(); }
}