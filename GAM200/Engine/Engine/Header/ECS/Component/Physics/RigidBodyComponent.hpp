/* Start Header**********************************************************************************/
/*
@file    RigidBodyComponent.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    19/06/2021
@brief
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

#include "Engine/Header/Math/MathLib.hpp"


namespace Engine {
	class DSerializer;
	class SSerializer;

	struct RigidBodyComponent : public IComponent {
		float speed = float{};
		//Higher = stop faster
		//float friction = float{};
		bool isActive = true;

		RigidBodyComponent& Deserialize(const DSerializer& _serializer);
		void Serialize(const SSerializer& _serializer);

		RigidBodyComponent(Entity_id _ID = DEFAULT_ENTITY_ID, bool _active = true);
	};
}

#endif