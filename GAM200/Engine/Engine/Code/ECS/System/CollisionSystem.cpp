/* Start Header**********************************************************************************/
/*
@file    CollisionSystem.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
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
#include "Engine/Header/Physics/Collision.hpp"

#include "Engine/Header/Event/OverlapColliderEvent.hpp"
#include "Engine/Header/Event/EventDispatcher.hpp"

#include "Engine/Header/ECS/Component/Physics/ColliderComponent.hpp"
#include "Engine/Header/ECS/Component/Physics/RigidBodyComponent.hpp"
#include "Engine/Header/ECS/Component/Graphics/TransformComponent.hpp"

#include "Engine/Header/ECS/DreamECS.hpp"

#include "Engine/Header/Math/MathLib.hpp"

#include "Engine/Header/Debug Tools/Profiler.hpp"

#include "Engine/Header/Physics/Ray.hpp" //Ray

#include "Engine/Header/Time/DeltaTime.hpp"

namespace Engine {
	std::unordered_map<Entity_id, std::vector<Entity>> overlapMap;

	//Called when removing dead entities
	void CollisionSystem::RemoveDeadEntity(Entity_id deadEntity) {
		//---------------Check for dead entity / Disabled collider-------------------
		//const EntityMapType& emt = dreamECSGame->GetUsedConstEntityMap();
		//std::set<Entity_id> removeSet{};
		if (overlapMap.find(deadEntity) == overlapMap.end()) return;

		auto& vecId = overlapMap[deadEntity];
		for (auto& entId : vecId) {
			const auto& iter1 = overlapMap.find(entId.id);
			if (iter1 == overlapMap.end()) continue;

			size_t size1 = iter1->second.size();
			std::set<size_t> removeCount{};
			for (size_t i = 0; i < size1; i++) {
				if (iter1->second[i].id != deadEntity) continue;

				removeCount.insert(i);

				MonoFunctionType type;
				ColliderComponent* cc = dreamECSGame->GetComponentPTR<ColliderComponent>(entId.id);
				if (cc == nullptr) continue;
				if (cc->isTrigger)
					type = MonoFunctionType::Trigger_Exit;
				else
					type = MonoFunctionType::Collision_Exit;

				OverlapColliderEvent event(entId.id, deadEntity, type);
				EventDispatcher::SendEvent(event);

				break;
			}

			for (auto i : removeCount) {
				overlapMap[entId.id].erase(iter1->second.begin() + i);
			}
		}

		overlapMap.erase(deadEntity);
		//for (auto& i : removeSet) {
		//	overlapMap.erase(i);
		//}
	}

	bool AddOverlap(Entity_id lhs, bool lhsTrigger, Entity_id rhs, bool rhsTrigger) {
		PROFILER_START("Collision");

		//if self is collision and other is trigger, OnCollisionEnter is not called
		if (!lhsTrigger && rhsTrigger) return false;

		const auto& iter = overlapMap.find(lhs);
		if (iter != overlapMap.end()) {
			//if map exist means that it already collided/triggered
			for (const auto& ent : iter->second) {
				if (ent.id == rhs) {
					MonoFunctionType type;
					if (lhsTrigger)
						type = MonoFunctionType::Trigger_Stay;
					else
						type = MonoFunctionType::Collision_Stay;

					OverlapColliderEvent event(lhs, rhs, type);
					EventDispatcher::SendEvent(event);
					return true;
				}
			}
		}

		overlapMap[lhs].emplace_back(rhs);
		MonoFunctionType type;
		if (lhsTrigger)
			type = MonoFunctionType::Trigger_Enter;
		else
			type = MonoFunctionType::Collision_Enter;

		OverlapColliderEvent event(lhs, rhs, type);
		EventDispatcher::SendEvent(event);

		return true;
	}

	void CollisionSystem::Update(float) {
		PROFILER_START("Collision");

		auto& colliderArray = dreamECSGame->GetComponentArrayData<ColliderComponent>();
		auto colliderStart = colliderArray.begin(),
			colliderEnd = colliderArray.end();
		for (auto& col1 = colliderStart; col1 < colliderEnd; col1++) {
			const Entity_id& entity_id1 = col1->GetEntityId();
			if (EntityId_Check(entity_id1)) break;
			if (!col1->isActive) continue;

			TransformComponent* transform1 = dreamECSGame->GetComponentPTR<TransformComponent>(entity_id1);
			if (transform1 == nullptr || !transform1->isActive) continue;

			ColliderComponent collider1 = *col1;
			collider1.offset_position += Math::vec2{ transform1->position };
			collider1.offset_scale *= transform1->scale;
			collider1.angle += transform1->angle;

			/*
			* Start of collision checks
			*/
			for (auto col2 = col1; col2 < colliderEnd; col2++) {
				const Entity_id& entity_id2 = col2->GetEntityId();
				if (EntityId_Check(entity_id2)) break;
				if (!col2->isActive || col1 == col2) continue;
				const RigidBodyComponent* rb1 = dreamECSGame->GetComponentPTR<RigidBodyComponent>(entity_id1);
				const RigidBodyComponent* rb2 = dreamECSGame->GetComponentPTR<RigidBodyComponent>(entity_id2);
				bool ent1IsMoveable = (rb1 != nullptr) && rb1->isActive,
					ent2IsMoveable = (rb2 != nullptr) && rb2->isActive;

				
				
				TransformComponent* transform2 = dreamECSGame->GetComponentPTR<TransformComponent>(entity_id2);
				if (transform2 == nullptr || !transform2->isActive) continue;

				//if (transform1->layer != transform2->layer) continue; //collision layer

				ColliderComponent collider2 = *col2;
				collider2.offset_position += Math::vec2{ transform2->position };
				collider2.offset_scale *= transform2->scale;
				collider2.angle += transform2->angle;

				//If one of it is trigger then rigidbody is not needed
				if (!(collider1.isTrigger) && !(collider2.isTrigger))
					if (!ent1IsMoveable && !ent2IsMoveable) continue;
				
				//Direction from collider2 towards collider1 (Set by isColliding
				Math::vec2 dir = Math::vec2{};

				if (CollisionImplementation::isColliding(dir, collider1, ent1IsMoveable,
					collider2, ent2IsMoveable)) {
					//std::cout << collider1.offset_position << " and " << collider2.offset_position << " with result collided "<< entity_id1 << " vs " << entity_id2 << "\n";
					if (!AddOverlap(entity_id1, collider1.isTrigger, entity_id2, collider2.isTrigger)) continue;
					if (!AddOverlap(entity_id2, collider2.isTrigger, entity_id1, collider1.isTrigger)) continue;

					if (collider1.isTrigger || collider2.isTrigger) {
						LOG_INFO("Trigger");
						continue;
					}

					//A bit of a hack
					//To prevent object from sharing the same position
					//by moving it slightly out of each other and setting a direction
					//as previous direction would be dividing by 0
					Math::vec2 EpsilonCheck = collider2.offset_position - collider1.offset_position;
					if (EpsilonCheck.x < Math::epsilon<float>() && EpsilonCheck.x > -Math::epsilon<float>() &&
						EpsilonCheck.y < Math::epsilon<float>() && EpsilonCheck.y > -Math::epsilon<float>()) {

						collider1.offset_position.x -= 0.5f * transform1->scale.x;
						transform1->position.x -= 0.5f * transform1->scale.x;
						dir = Math::vec2{ 1.f, 0.f };
					}
					CollisionImplementation::CollisionResolution(dir, *transform1, collider1, *transform2, collider2);
				}

				else {
					//std::cout << entity_id1 << " vs " << entity_id2 << " not collided \n";
					const auto& iter1 = overlapMap.find(entity_id1);
					if (iter1 != overlapMap.end()) {
						size_t size1 = iter1->second.size();
						std::set<size_t> removeCount{};
						for (size_t i = 0; i < size1; i++) {
							if (iter1->second[i].id == entity_id2) {
								removeCount.insert(i);
								//overlapMap[entity_id1].erase(iter1->second.begin() + i);

								MonoFunctionType type;
								if (collider1.isTrigger)
									type = MonoFunctionType::Trigger_Exit;
								else
									type = MonoFunctionType::Collision_Exit;

								OverlapColliderEvent event(entity_id1, entity_id2, type);
								EventDispatcher::SendEvent(event);
								break;
							}
						}

						for (auto i : removeCount) {
							overlapMap[entity_id1].erase(iter1->second.begin() + i);
						}
					}
					const auto& iter2 = overlapMap.find(entity_id2);
					if (iter2 != overlapMap.end()) {
						size_t size2 = iter2->second.size();
						std::set<size_t> removeCount{};
						for (size_t i = 0; i < size2; i++) {
							if (iter2->second[i].id == entity_id1) {
								removeCount.insert(i);
								//overlapMap[entity_id2].erase(iter2->second.begin() + i);

								MonoFunctionType type;
								if (collider2.isTrigger)
									type = MonoFunctionType::Trigger_Exit;
								else
									type = MonoFunctionType::Collision_Exit;

								OverlapColliderEvent event(entity_id2, entity_id1, type);
								EventDispatcher::SendEvent(event);
								break;
							}
						}

						for (auto i : removeCount) {
							overlapMap[entity_id2].erase(iter2->second.begin() + i);
						}
					}
				}
			}
		}
	}

	bool CollisionSystem::RayCast(const Ray& ray, RaycastHit* hit, std::uint32_t ignoreTarget) {
		PROFILER_START("Collision");

		auto& colliderArray = dreamECSGame->GetComponentArrayData<ColliderComponent>();
		for (const auto& col : colliderArray) {
			const Entity_id& entity_id = col.GetEntityId();
			if (entity_id == ignoreTarget) continue;
			if (EntityId_Check(entity_id)) break;
			if (!col.isActive) continue;

			auto& transform = dreamECSGame->GetComponent<TransformComponent>(entity_id);
			if (!transform.isActive) continue;

			RaycastHit hitTarget;
			if (CollisionImplementation::RayCast_Internal(ray, transform, col, &hitTarget)) {
				*hit = hitTarget;
				hit->entity_id = entity_id;
				return true;
			}
		}

		return false;
	}

	bool CollisionSystem::RayCastGroup(const Ray& ray, RaycastHit(&rayCastHit)[10], int* count, std::uint32_t ignoreTarget) {
		PROFILER_START("Collision");

		*count = 0;
		auto& colliderArray = dreamECSGame->GetComponentArrayData<ColliderComponent>();
		for (const auto& col : colliderArray) {
			const Entity_id& entity_id = col.GetEntityId();
			if (entity_id == ignoreTarget) continue;
			if (EntityId_Check(entity_id)) break;
			if (!col.isActive) continue;

			auto& transform = dreamECSGame->GetComponent<TransformComponent>(entity_id);
			if (!transform.isActive) continue;

			RaycastHit hitTarget;
			if (CollisionImplementation::RayCast_Internal(ray, transform, col, &hitTarget)) {
				RaycastHit& rch = rayCastHit[*count];
				rch = hitTarget;
				rch.entity_id = entity_id;
				++(*count);
				if ((*count) == 10) break;

			}
		}

		//if (*count > 0) {
		//	std::cout << "hit " << *count << " ";
		//	for (int i = 0; i < *count; i++) {
		//		std::cout << rayCastHit[i].entity_id << " ";
		//	}
		//	std::cout << "\n-----------------------------------------------\n\n";
		//}


		if ((*count) > 0) return true;
		return false;
	}

	void CollisionSystem::Stop() {
		PROFILER_START("Collision");

		overlapMap.clear();
	}

	bool CollisionSystem::Create() {
		LOG_INSTANCE("Collision System created");
		return true;
	}
	void CollisionSystem::Destroy() {
		LOG_INSTANCE("Collision System destroyed");
	}
}