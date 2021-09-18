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
	Collider::Collider(Entity _ID, ColliderType _c, Math::vec2 _pos, Math::vec2 _scale, float _rotation, bool _trigger, bool _active) :
		IComponent{ _ID }, cType{ _c }, offset_position{ _pos }, offset_scale{ _scale }, angle{ _rotation }, isTrigger{ _trigger }, isActive{ _active } {}

	Collider Collider::Deserialize(const DSerializer& _serializer) {
		cType = ColliderType(_serializer.GetValue<int>("ColliderType"));
		offset_position = _serializer.GetValue<Math::vec2>("Position");
		offset_scale = _serializer.GetValue<Math::vec2>("Scale");
		angle = _serializer.GetValue<float>("Angle");
		isTrigger = _serializer.GetValue<bool>("IsTrigger");
		isActive = _serializer.GetValue<bool>("IsActive");
		return *this;
	}

	void Collider::Serialize(const SSerializer& _serializer) {
		_serializer.SetValue("ColliderType", (int)cType);
		_serializer.SetValue("Position", offset_position);
		_serializer.SetValue("Scale", offset_scale);
		_serializer.SetValue("Angle", angle);
		_serializer.SetValue("IsTrigger", isTrigger);
		_serializer.SetValue("IsActive", isActive);

		_serializer.EndSerialize("Collider");	
	}
}