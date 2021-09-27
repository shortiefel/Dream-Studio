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

namespace Engine {
	void PhysicsSystem::Update(float dt) {
		const auto& rigidBodyArray = DreamECS::GetInstance().GetComponentArrayData<RigidBody>();
		for (auto& rigidBody : rigidBodyArray) {
			Entity currentEntity = rigidBody.GetEntityId();
			if (Entity_Check(currentEntity)) break;
			if (!rigidBody.isActive) continue;

			TransformComponent* transform = DreamECS::GetInstance().GetComponentTest<TransformComponent>(currentEntity);
			if (!transform || !transform->isActive) continue;

			Physics::ApplyLinearVelocity(transform->position, transform->angle, rigidBody.speed * dt);
			//transform->position += Math::vec2{ std::cos(Math::radians((float)transform->angle)), std::sin(Math::radians((float)transform->angle)) } * dt;
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
