/* Start Header**********************************************************************************/
/*
@file    TransformComponent.cpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    16/09/2021
\brief
This file contain the transform struct to be used by the ECS and various system

//Serialize list
-vec2 float:	Position
-vec2 float:    Scale
-string:		Shape
-string:		Shader


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/ECS/Component/Graphics/TransformComponent.hpp"

namespace Engine {
	Transform::Transform(Entity _ID, Math::vec2 _pos, Math::vec2 _scale, float _angle, bool _active, int _layer) :
		IComponent{ _ID },
		position{ _pos }, scale{ _scale }, angle{ _angle },
		isActive{ _active }, layer{ _layer } {}

	Math::mat3 Transform::GetTransform() const {
		return
			//Translation
			Math::mat3{ Math::vec3(1.f, 0, 0),
						  Math::vec3(0, 1.f, 0),
						  Math::vec3(position.x, position.y, 1.f) }
			*
			Math::mat3{ Math::vec3(std::cos(Math::radians(angle)), std::sin(Math::radians(angle)), 0),
						  Math::vec3(-std::sin(Math::radians(angle)), std::cos(Math::radians(angle)), 0),
						  Math::vec3(0.f, 0.f, 1.f) }
			*
			//Scale
			Math::mat3{ Math::vec3(scale.x, 0, 0),
						 Math::vec3(0, scale.y, 0),
						 Math::vec3(0, 0, 1.f) };
	}

	Transform Transform::Deserialize(const DSerializer& _serializer) {
		position = _serializer.GetValue<Math::vec2>("Position");
		scale = _serializer.GetValue<Math::vec2>("Scale");
		angle = _serializer.GetValue<float>("Angle");
		isActive = _serializer.GetValue<bool>("IsActive");
		return *this;
	}

	void Transform::Serialize(const SSerializer& _serializer) {
		_serializer.SetValue("Position", position);
		_serializer.SetValue("Scale", scale);
		_serializer.SetValue("Angle", angle);
		_serializer.SetValue("IsActive", isActive);

		//_serializer.EndSerialize("Transform");
	}
}