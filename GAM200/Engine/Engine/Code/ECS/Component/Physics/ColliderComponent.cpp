/* Start Header**********************************************************************************/
/*
@file    ColliderComponent.cpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    16/09/2021
\brief
This file contain the definition for ColliderComponent


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/ECS/Component/Physics/ColliderComponent.hpp"

namespace Engine {
	/*Collider::Collider(Entity ID, ColliderType c, bool trigger) :
		IComponent{ ID }, cType{ c }, offset_position{ Math::vec2{ 0.f, 0.f } }, offset_scale{ Math::vec2{ 0.f, 0.f } }, angle{ 0.f }, isTrigger{ trigger } {}*/

	//Change of type constructor: Copy an existing Collider but with a different type
	Collider::Collider(Entity ID, ColliderType c, Math::vec2 tPos, Math::vec2 tScale, float rotation, bool tTrigger, bool active) :
		IComponent{ ID }, cType{ c }, offset_position{ tPos }, offset_scale{ tScale }, angle{ rotation }, isTrigger{ tTrigger }, isActive{ active } {}

	Collider Collider::Deserialize(const Serializer& serializer) {
		cType = ColliderType(serializer.GetValue<int>("ColliderType"));
		offset_position = serializer.GetValue<Math::vec2>("Position");
		offset_scale = serializer.GetValue<Math::vec2>("Scale");
		angle = serializer.GetValue<float>("Angle");
		isTrigger = serializer.GetValue<bool>("IsTrigger");
		isActive = serializer.GetValue<bool>("IsActive");
		return *this;
	}

	void Collider::Serialize(const Serializer& serializer) {

	}
}