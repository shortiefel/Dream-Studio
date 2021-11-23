/* Start Header**********************************************************************************/
/*
@file    TransformComponent.cpp
@author  Chia Yi Da		c.yida@digipen.edu	100%
@date    19/06/2021
\brief
This file contains the TransformComponent definition


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Debug Tools/Logging.hpp"

#include "Engine/Header/ECS/Component/Graphics/TransformComponent.hpp"

#include "Engine/Header/Serialize/DSerializer.hpp"
#include "Engine/Header/Serialize/SSerializer.hpp"

// MACRO
#define rad(ang) \
	Math::radians((float)ang)

namespace Engine
{
	// Contructor for Transform Component
	TransformComponent::TransformComponent(Entity_id _ID, Math::vec2 _pos, Math::vec2 _scale,
		float _angle, int _layer, bool _active) :
		IComponent{ _ID }, position{ _pos }, localPosition{ _pos }, scale{ _scale },
		angle{ _angle }, layer{ _layer }, isActive{ _active } {}

	// Operator overloading += for Transform Component
	TransformComponent& TransformComponent::operator+= (const TransformComponent& _rhs)
	{
		position += _rhs.position;
		scale *= _rhs.scale;
		angle += _rhs.angle;

		return *this;
	}

	// Deserialize function for Transform Component
	TransformComponent& TransformComponent::Deserialize(const DSerializer& _serializer)
	{
		position = _serializer.GetValue<Math::vec2>("Position");
		localPosition = _serializer.GetValue<Math::vec2>("LocalPosition");

		scale = _serializer.GetValue<Math::vec2>("Scale");
		angle = _serializer.GetValue<float>("Angle");

		layer = _serializer.GetValue<int>("Layer");
		isActive = _serializer.GetValue<bool>("IsActive");

		return *this;
	}

	// Serialize function for Transform Component
	void TransformComponent::Serialize(const SSerializer& _serializer)
	{
		_serializer.SetValue("Position", position);
		_serializer.SetValue("LocalPosition", localPosition);

		_serializer.SetValue("Scale", scale);
		_serializer.SetValue("Angle", angle);

		_serializer.SetValue("Layer", layer);
		_serializer.SetValue("IsActive", isActive);
	}
}

// Code that might be used for the future

/*
Math::mat3 TransformComponent::GetTransform() const
{
	return
		//Translation
		Math::mat3{ Math::vec3(1.f, 0, 0),
					Math::vec3(0, 1.f, 0),
					Math::vec3(position.x, position.y, 1.f) }
		*
		Math::mat3{ Math::vec3(std::cos(rad((float)angle)), std::sin(rad((float)angle)), 0),
					Math::vec3(-std::sin(rad((float)angle)), std::cos(rad((float)angle)), 0),
					Math::vec3(0.f, 0.f, 1.f) }
		*
		//Scale
		Math::mat3{ Math::vec3(scale.x, 0, 0),
					Math::vec3(0, scale.y, 0),
					Math::vec3(0, 0, 1.f) };
}
*/

/*
Math::vec2 TransformComponent::GetTruePosition() const {
	auto& tem = DreamECS::GetInstance().GetUsedConstEntityMap();

	Entity_id _parent = DEFAULT_ENTITY_ID;
	const auto & itr = tem.find(GetEntityId());
	if (itr != tem.end()) {
		_parent = itr->second.parent;
	}

	if (_parent != DEFAULT_ENTITY_ID) {
		return position + DreamECS::GetInstance().GetComponent<TransformComponent>(_parent).GetTruePosition();
	}
	return position;
}
*/