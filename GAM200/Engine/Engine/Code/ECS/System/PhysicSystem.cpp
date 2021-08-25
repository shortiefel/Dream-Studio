/* Start Header**********************************************************************************/
/*
@file    PhysicSystem.cpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    19/06/2021
\brief
This file has the function definition for class PhysicSystem

collider only store offset from transform position
in update transform position and scale is added to collider position and scale as
collision checks only takes in collider


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/


#include "Engine/Header/Debug Tools/Logging.hpp"
#include "Engine/Header/ECS/System/PhysicSystem.hpp"
#include "Engine/Header/Physic/Physic.hpp"

#include "Engine/Header/ECS/Component/Physics/ColliderComponent.hpp"
#include "Engine/Header/ECS/Component/Graphics/TransformComponent.hpp"

#include "Engine/Header/ECS/Coordinator.hpp"

#include <glm/gtc/constants.hpp>

namespace Engine {
	extern Coordinator gCoordinator;
	std::shared_ptr<PhysicSystem> PhysicSystem::PS;

	//Static--------------------------------------------------------
	//PhysicSystem* PhysicSystem::s_instance = 0;
	//PhysicSystem* PhysicSystem::Get() { return s_instance; }

	//---------------------------------------------------------------

	void PhysicSystem::Update(float dt) {
		//For all entities in PhysicSystem
		for (std::set<Entity>::iterator entity1 = PS->mEntities.begin(); entity1 != PS->mEntities.end(); ++entity1) {
			//for (auto const& entity1 : mEntities) {
			auto& transform1 = gCoordinator.GetCom<Transform>(*entity1);
			auto collider1 = gCoordinator.GetCom<Collider>(*entity1);

			collider1.offset_position += glm::vec2{ transform1.position };
			collider1.offset_scale += transform1.scale;

			for (std::set<Entity>::iterator entity2 = entity1; entity2 != PS->mEntities.end(); ++entity2) {
				//for (auto const& entity2 : mEntities) {
				if (entity1 == entity2) continue;
				auto& transform2 = gCoordinator.GetCom<Transform>(*entity2);
				auto collider2 = gCoordinator.GetCom<Collider>(*entity2);

				collider2.offset_position += glm::vec2{ transform2.position };
				collider2.offset_scale += transform2.scale;

				//Apply gravity if rigidbody exist and rigidbody hasGravity

				//Direction from collider2 towards collider1
				glm::vec2 dir = glm::vec2{};
				if (!PhysicImplementation::isColliding(dir, collider1, collider2)) {

				}

				else if (collider1.isTrigger || collider2.isTrigger) {
					LOG_INFO("Trigger");
				}

				//else resolve collision by pushing object out
				else {
					//A bit of a hack
					//To prevent object from sharing the same position
					//by moving it slightly out of each other and setting a direction
					//as previous direction would be dividing by 0
					glm::vec2 EpsilonCheck = collider2.offset_position - collider1.offset_position;
					if (EpsilonCheck.x < glm::epsilon<float>() && EpsilonCheck.x > -glm::epsilon<float>() &&
						EpsilonCheck.y < glm::epsilon<float>() && EpsilonCheck.y > -glm::epsilon<float>()) {
						std::cout << "too close \n";
						collider1.offset_position.x -= 0.3f * transform1.scale.x;
						transform1.position.x -= 0.3f * transform1.scale.x;
						dir = glm::vec2{ 1.f, 0.f };
					}
					PhysicImplementation::CollisionResolution(dir, transform1, collider1, transform2, collider2);
				}


			}
		}
	}

	bool PhysicSystem::Create(const std::shared_ptr<PhysicSystem>& physicSystem) {
		PS = physicSystem;
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