/* Start Header**********************************************************************************/
/*
@file    RigidBodyComponent.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    19/06/2021
@brief
#include "Engine/Header/ECS/Component/RigidBodyComponent.hpp"
This file contain the RigidBody struct to be used by the ECS and various system


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Engine/Header/ECS/Component/IComponent.hpp"
#include "Engine/Header/Physics/Forces.hpp"

#include "Engine/Header/Math/MathLib.hpp"

#include <list>

namespace Engine {
	class DSerializer;
	class SSerializer;

	struct RigidBodyComponent : public IComponent {
		//To Display
		float speed = float{};
		//Display as Mass but recorded as inverse mass
		int mass = 1;
		float linearDrag = 0.f;
		float angularDrag = 0.f;
		
		bool isActive = true;
		
		Math::vec2 linearVelocity = Math::vec2{ 0.f, 0.f };
		Math::vec2 linearAcceleration = Math::vec2{ 0.f, 0.f };
		float angularVelocity = 0.f;
		float angularAcceleration = 0.f;

		std::list<LinearForces> linearForces;
		std::list<RotationForces> rotationForces;

		RigidBodyComponent& Deserialize(const DSerializer& _serializer);
		void Serialize(const SSerializer& _serializer);

		RigidBodyComponent(Entity_id _ID = DEFAULT_ENTITY_ID, bool _active = true);
	};
}

#endif