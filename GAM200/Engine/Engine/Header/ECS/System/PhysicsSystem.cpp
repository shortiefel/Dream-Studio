/* Start Header**********************************************************************************/
/*
@file    PhysicsSystem.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    23/09/2021
\brief
This file has the class definition for PhysicsSystem


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Debug Tools/Logging.hpp"

#include "Engine/Header/Physics/Physics.hpp"

#include "Engine/Header/ECS/System/PhysicsSystem.hpp"
#include "Engine/Header/ECS/Component/Physics/RigidBodyComponent.hpp"

#include "Engine/Header/ECS/DreamECS.hpp"

#include "Engine/Header/Debug Tools/Profiler.hpp"

namespace Engine {
	void PhysicsSystem::Update(float dt) {
		PROFILER_START("Physics");

		const auto& rigidBodyArray = DreamECS::GetInstance().GetComponentArrayData<RigidBodyComponent>();
		for (auto& rigidBody : rigidBodyArray) {
			const Entity& entity = rigidBody.GetEntity();
			if (Entity_Check(entity)) break;
			if (!rigidBody.isActive) continue;

			TransformComponent* transform = DreamECS::GetInstance().GetComponentPTR<TransformComponent>(entity);
			if (!transform || !transform->isActive) continue;

			Physics::ApplyLinearVelocity(transform->position, transform->angle, rigidBody.speed * dt);
		}
	}

	bool PhysicsSystem::Create() {
		LOG_INSTANCE("Physics System created");
		return true;
	}
	void PhysicsSystem::Destroy() {
		LOG_INSTANCE("Physics System destroyed");
	}

}
