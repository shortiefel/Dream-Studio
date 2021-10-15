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

namespace Engine {
	std::unordered_map<Entity_id, std::vector<Entity>> overlapMap;

	void AddOverlap(Entity lhs, bool lhsTrigger, Entity rhs, bool rhsTrigger) {
		PROFILER_START("Collision");

		//if self is collision and other is trigger, OnCollisionEnter is not called
		if (!lhsTrigger && rhsTrigger) return;

		const auto& iter = overlapMap.find(lhs.id);
		if (iter != overlapMap.end()) {
			//if map exist means that it already collided/triggered
			for (const auto& ent : iter->second) {
				if (ent.id == rhs.id) {
					MonoFunctionType type;
					if (lhsTrigger)
						type = MonoFunctionType::TRIGGER_STAY;
					else
						type = MonoFunctionType::COLLISION_STAY;

					OverlapColliderEvent event(lhs.id, rhs.id, type);
					EventDispatcher::SendEvent(event);
					return;
				}
			}
		}

		overlapMap[lhs.id].emplace_back(rhs);
		MonoFunctionType type;
		if (lhsTrigger)
			type = MonoFunctionType::TRIGGER_ENTER;
		else
			type = MonoFunctionType::COLLISION_ENTER;

		OverlapColliderEvent event(lhs.id, rhs.id, type);
		EventDispatcher::SendEvent(event);
	}

	void CollisionSystem::Update(float dt) {
		PROFILER_START("Collision");

		auto& colliderArray = DreamECS::GetInstance().GetComponentArrayData<ColliderComponent>();
		auto colliderStart = colliderArray.begin(),
			colliderEnd = colliderArray.end();
		for (auto& col1 = colliderStart; col1 < colliderEnd; col1++) {
			const Entity& ent1 = col1->GetEntity();
			if (Entity_Check(ent1)) break;
			if (!col1->isActive) continue;

			auto& transform1 = DreamECS::GetInstance().GetComponent<TransformComponent>(ent1);
			if (!transform1.isActive) continue;

			ColliderComponent collider1 = *col1;
			collider1.offset_position += Math::vec2{ transform1.position };
			collider1.offset_scale *= transform1.scale;
			collider1.angle += transform1.angle;

			/*
			* Start of collision checks
			*/
			for (auto col2 = col1; col2 < colliderEnd; col2++) {
				const Entity& ent2 = col2->GetEntity();
				if (Entity_Check(ent2)) break;
				if (!col2->isActive || col1 == col2) continue;

				bool ent1IsMoveable = DreamECS::GetInstance().HasComponentCheck<RigidBodyComponent>(ent1),
					ent2IsMoveable = DreamECS::GetInstance().HasComponentCheck<RigidBodyComponent>(ent2);
				if (!ent1IsMoveable && !ent2IsMoveable) continue;

				auto& transform2 = DreamECS::GetInstance().GetComponent<TransformComponent>(ent2);
				if (!transform2.isActive) continue;

				ColliderComponent collider2 = *col2;
				collider2.offset_position += Math::vec2{ transform2.position };
				collider2.offset_scale *= transform2.scale;
				collider2.angle += transform2.angle;

				//Direction from collider2 towards collider1
				Math::vec2 dir = Math::vec2{};

				if (CollisionImplementation::isColliding(dir, collider1, ent1IsMoveable,
					collider2, ent2IsMoveable)) {

					AddOverlap(ent1, collider1.isTrigger, ent2, collider2.isTrigger);
					AddOverlap(ent2, collider2.isTrigger, ent1, collider1.isTrigger);

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
						
						collider1.offset_position.x -= 0.5f * transform1.scale.x;
						transform1.position.x -= 0.5f * transform1.scale.x;
						dir = Math::vec2{ 1.f, 0.f };
					}
					CollisionImplementation::CollisionResolution(dir, transform1, collider1, transform2, collider2);
				}

				else {
					const auto& iter1 = overlapMap.find(ent1.id);
					if (iter1 != overlapMap.end()) {
						size_t size1 = iter1->second.size();
						for (size_t i = 0; i < size1; i++) {
							if (iter1->second[i].id == ent2.id) {
								overlapMap[ent1.id].erase(iter1->second.begin() + i);

								MonoFunctionType type;
								if (collider1.isTrigger)
									type = MonoFunctionType::TRIGGER_EXIT;
								else
									type = MonoFunctionType::COLLISION_EXIT;

								OverlapColliderEvent event(ent1.id, ent2.id, type);
								EventDispatcher::SendEvent(event);
								break;
							}
						}
					}
					const auto& iter2 = overlapMap.find(ent2.id);
					if (iter2 != overlapMap.end()) {
						size_t size2 = iter2->second.size();
						for (size_t i = 0; i < size2; i++) {
							if (iter2->second[i].id == ent1.id) {
								overlapMap[ent2.id].erase(iter2->second.begin() + i);

								MonoFunctionType type;
								if (collider2.isTrigger)
									type = MonoFunctionType::TRIGGER_EXIT;
								else
									type = MonoFunctionType::COLLISION_EXIT;

								OverlapColliderEvent event(ent2.id, ent1.id, type);
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