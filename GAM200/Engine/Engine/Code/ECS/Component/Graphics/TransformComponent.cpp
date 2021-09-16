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
	Transform::Transform(Entity ID, Math::vec2 tPos, Math::vec2 tScale, float rotationAngle, bool active, int tLayer) :
		IComponent{ ID },
		position{ tPos }, scale{ tScale }, angle{ rotationAngle },
		isActive{ active }, layer{ tLayer } {}

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

	Transform Transform::Deserialize(const Serializer& serializer) {
		position = serializer.GetValue<Math::vec2>("Position");
		scale = serializer.GetValue<Math::vec2>("Scale");
		angle = serializer.GetValue<float>("Angle");
		isActive = serializer.GetValue<bool>("IsActive");
		return *this;
	}

	void Transform::Serialize(const Serializer& serializer) {

	}
}