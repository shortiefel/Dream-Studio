/* Start Header**********************************************************************************/
/*
@file    RegidBodyComponent.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    16/09/2021
\brief
This file contain the definition for RegidBodyComponent


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/ECS/Component/Physics/RigidBodyComponent.hpp"

#include "Engine/Header/Serialize/DSerializer.hpp"
#include "Engine/Header/Serialize/SSerializer.hpp"

namespace Engine {
	RigidBodyComponent::RigidBodyComponent(Entity_id _ID, bool _active) : IComponent{ _ID }, isActive{ _active } {}

	RigidBodyComponent& RigidBodyComponent::Deserialize(const DSerializer& _serializer) {
		speed = _serializer.GetValue<float>("Speed");

		mass = _serializer.GetValue<int>("Mass");
		/*linearVelocity = _serializer.GetValue<float>("LinearVelocity");
		linearAcceleration = _serializer.GetValue<Math::vec2>("LinearAcceleration");*/
		linearDrag = _serializer.GetValue<float>("LinearDrag");

		/*angularVelocity = _serializer.GetValue<float>("AngularVelocity");
		angularAcceleration = _serializer.GetValue<float>("AngularAcceleration");*/
		angularDrag = _serializer.GetValue<float>("AngularDrag");

		isActive = _serializer.GetValue<bool>("IsActive");
		return *this;
	}

	void RigidBodyComponent::Serialize(const SSerializer& _serializer) {
		_serializer.SetValue("Speed", speed);

		_serializer.SetValue("Mass", mass);
		_serializer.SetValue("LinearDrag", linearDrag);
		_serializer.SetValue("AngularDrag", angularDrag);

		_serializer.SetValue("IsActive", isActive);

		//_serializer.EndSerialize("RigidBody");
	}
}