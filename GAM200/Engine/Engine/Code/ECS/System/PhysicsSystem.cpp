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
#include "Engine/Header/Parent/ParentManager.hpp"

#include "Engine/Header/ECS/System/PhysicsSystem.hpp"
#include "Engine/Header/ECS/Component/Physics/RigidBodyComponent.hpp"
#include "Engine/Header/ECS/DreamECS.hpp"

#include "Engine/Header/Debug Tools/Profiler.hpp"

#include "Engine/Header/Time/DeltaTime.hpp"

namespace Engine {
	void PhysicsSystem::Update(float dt) {
		PROFILER_START("Physics");

		auto& rigidBodyArray = dreamECSGame->GetComponentArrayData<RigidBodyComponent>();
		for (auto& rigidBody : rigidBodyArray) {
			const Entity_id& entity_id = rigidBody.GetEntityId();
			if (EntityId_Check(entity_id)) break;
			if (!rigidBody.isActive) continue;

			TransformComponent* transform = dreamECSGame->GetComponentPTR<TransformComponent>(entity_id);
			if (!transform || !transform->isActive) continue;

			//Physics::ApplyLinearVelocity(transform->localPosition, transform->angle, rigidBody.speed * dt);

			//Linear Physics
			std::list<LinearForces> tempLinearForces;
			Math::vec2 summedForces = Math::vec2{ 0.f, 0.f };
			for (auto& lForce : rigidBody.linearForces) {
				summedForces += lForce.direction * lForce.magnitude;
				lForce.magnitude -= rigidBody.linearDrag;

				if (lForce.magnitude > 0.f) tempLinearForces.emplace_back(lForce);
			}
			rigidBody.linearForces = tempLinearForces;
			rigidBody.linearAcceleration = summedForces / rigidBody.mass;
			rigidBody.linearVelocity = rigidBody.linearVelocity + rigidBody.linearAcceleration * dt;
			TransformComponent& trans = *transform;
			size_t linearForcesSz = rigidBody.linearForces.size();
			if (linearForcesSz == 0 && rigidBody.linearDrag > 0.f)
				rigidBody.linearVelocity = rigidBody.linearVelocity - rigidBody.linearVelocity * dt * rigidBody.linearDrag / rigidBody.mass;
			if (linearForcesSz >= 20) rigidBody.linearForces.clear();
			trans.localPosition = trans.localPosition + rigidBody.linearVelocity * dt;
			ParentManager::GetInstance().UpdateTruePos(entity_id);
#if 0
			//Angular physics
			std::list<RotationForces> tempRotationForces;
			float summedTorque = 0.f;
			for (auto& rForce : rigidBody.rotationForces) {
				summedTorque += rForce.torque * rForce.direction;
				rForce.torque -= rigidBody.angularDrag;
				
				if (rForce.torque > 0.f) tempRotationForces.emplace_back(rForce);
			}
			rigidBody.rotationForces = tempRotationForces;
			rigidBody.angularAcceleration = summedTorque / rigidBody.mass;
			rigidBody.angularVelocity = rigidBody.angularVelocity + rigidBody.angularAcceleration * dt;

			size_t linearRotationSz = rigidBody.rotationForces.size();
			if ((linearRotationSz == 0 && rigidBody.angularDrag > 0.f) || (rigidBody.angularVelocity * summedTorque) < 0.f)
				rigidBody.angularVelocity = rigidBody.angularVelocity - rigidBody.angularVelocity * dt * rigidBody.angularDrag / rigidBody.mass;
			if (linearRotationSz >= 20) rigidBody.rotationForces.clear();

			trans.angle = trans.angle + rigidBody.angularVelocity * dt;
#endif

			if (trans.angle < -360.f) trans.angle = 360.f;
			else if (trans.angle > 360.f) trans.angle = 0.f;
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
