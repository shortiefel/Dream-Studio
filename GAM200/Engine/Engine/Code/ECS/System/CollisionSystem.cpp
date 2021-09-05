/* Start Header**********************************************************************************/
/*
@file    CollisionSystem.cpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    19/06/2021
\brief
This file has the function definition for class CollisionSystem

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
#include "Engine/Header/ECS/System/CollisionSystem.hpp"
#include "Engine/Header/Physic/Collision.hpp"

#include "Engine/Header/Event/OverlapColliderEvent.hpp"
#include "Engine/Header/Event/EventDispatcher.hpp"

#include "Engine/Header/ECS/Component/Physics/ColliderComponent.hpp"
#include "Engine/Header/ECS/Component/Physics/RigidBodyComponent.hpp"
#include "Engine/Header/ECS/Component/Graphics/TransformComponent.hpp"

#include "Engine/Header/ECS/Coordinator.hpp"

#include <glm/gtc/constants.hpp>

namespace Engine {
	extern Coordinator gCoordinator;
	std::shared_ptr<CollisionSystem> CollisionSystem::CS;
	std::unordered_map<Entity, std::vector<Entity>> overlapMap;

	void AddOverlap(Entity lhs, bool lhsTrigger, Entity rhs, bool rhsTrigger) {
		//if self is collision and other is trigger, OnCollisionEnter is not called
		if (!lhsTrigger && rhsTrigger) return;

		//if map for Entity doesnt exist
		//Vector should exist too so emplace back then end function
		const auto& iter = overlapMap.find(lhs);
		if (iter == overlapMap.end()) {
			overlapMap.emplace(lhs, std::vector<Entity>{});
			overlapMap[lhs].emplace_back(rhs);

			OverlapType type;
			if (lhsTrigger)
				type = OverlapType::OnTriggerEnter;
			else
				type = OverlapType::OnCollisionEnter;

			OverlapColliderEvent event(lhs, rhs, type);
			EventDispatcher::SendEvent(event);
			return;
		}

		//if map exist means that it already collided/triggered
		for (const auto& ent : iter->second) {
			if (ent == rhs) {
				OverlapType type;
				if (lhsTrigger)
					type = OverlapType::OnTriggerStay;
				else
					type = OverlapType::OnCollisionStay;

				OverlapColliderEvent event(lhs, rhs, type);
				EventDispatcher::SendEvent(event);
				return;
			}
		}

		overlapMap[lhs].emplace_back(rhs);
		OverlapType type;
		if (lhsTrigger)
			type = OverlapType::OnTriggerEnter;
		else
			type = OverlapType::OnCollisionEnter;

		OverlapColliderEvent event(lhs, rhs, type);
		EventDispatcher::SendEvent(event);
	}

	void CollisionSystem::Update(float dt) {
		//For all entities in CollisionSystem
		for (std::set<Entity>::iterator entity1 = CS->mEntities.begin(); entity1 != CS->mEntities.end(); ++entity1) {
			//for (auto const& entity1 : mEntities) {
			auto& transform1 = gCoordinator.GetCom<Transform>(*entity1);
			auto collider1 = gCoordinator.GetCom<Collider>(*entity1);

			/*collider1.offset_position += glm::vec2{ transform1.position };
			collider1.offset_scale *= transform1.scale;
			collider1.angle += transform1.angle;*/
			collider1.offset_position = glm::vec2{ transform1.position };
			collider1.offset_scale = transform1.scale;
			collider1.angle = transform1.angle;
			
			for (std::set<Entity>::iterator entity2 = entity1; entity2 != CS->mEntities.end(); ++entity2) {
				if (entity1 == entity2) continue;
				
				bool ent1IsMoveable = gCoordinator.HasComCheck<RigidBody>(*entity1),
					 ent2IsMoveable = gCoordinator.HasComCheck<RigidBody>(*entity2);
				if (!ent1IsMoveable && !ent2IsMoveable) continue;
				

				auto& transform2 = gCoordinator.GetCom<Transform>(*entity2);
				auto collider2 = gCoordinator.GetCom<Collider>(*entity2);

				/*collider2.offset_position += glm::vec2{ transform2.position };
				collider2.offset_scale *= transform2.scale;
				collider2.angle += transform2.angle;*/
				collider2.offset_position = glm::vec2{ transform2.position };
				collider2.offset_scale = transform2.scale;
				collider2.angle = transform2.angle;

				//Direction from collider2 towards collider1
				glm::vec2 dir = glm::vec2{};
				
				if (CollisionImplementation::isColliding(dir, collider1, ent1IsMoveable,
														      collider2, ent2IsMoveable)) {

					AddOverlap(*entity1, collider1.isTrigger, *entity2, collider2.isTrigger);
					AddOverlap(*entity2, collider2.isTrigger, *entity1, collider1.isTrigger);

					if (collider1.isTrigger || collider2.isTrigger) {
						LOG_INFO("Trigger");
						continue;
					}

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
					CollisionImplementation::CollisionResolution(dir, transform1, collider1, transform2, collider2);
				}

				else {
					
					
					const auto& iter1 = overlapMap.find(*entity1);
					if (iter1 != overlapMap.end()) {
						size_t size1 = iter1->second.size();
						for (size_t i = 0; i < size1; i++) {
							if (iter1->second[i] == *entity2) {
								overlapMap[*entity1].erase(iter1->second.begin() + i);
								
								OverlapType type;
								if (collider1.isTrigger)
									type = OverlapType::OnTriggerExit;
								else
									type = OverlapType::OnCollisionExit;

								OverlapColliderEvent event(*entity1, *entity2, type);
								EventDispatcher::SendEvent(event);
								break;
							}
						}
					}
					const auto& iter2 = overlapMap.find(*entity2);
					if (iter2 != overlapMap.end()) {
						size_t size2 = iter2->second.size();
						for (size_t i = 0; i < size2; i++) {
							if (iter2->second[i] == *entity1) {
								overlapMap[*entity2].erase(iter2->second.begin() + i);
								
								OverlapType type;
								if (collider2.isTrigger)
									type = OverlapType::OnTriggerExit;
								else
									type = OverlapType::OnCollisionExit;

								OverlapColliderEvent event(*entity2, *entity1, type);
								EventDispatcher::SendEvent(event);
								break;
							}
						}
					}
				}


			}
		}
	}

	void CollisionSystem::Stop() {
		overlapMap.clear();
	}

	bool CollisionSystem::Create(const std::shared_ptr<CollisionSystem>& collisionSystem) {
		CS = collisionSystem;
		LOG_INSTANCE("Collision System created");
		return true;
	}
	void CollisionSystem::Destroy() {
		LOG_INSTANCE("Collision System destroyed");
		//delete s_instance; 
	}

	CollisionSystem::~CollisionSystem() { Destroy(); }
}