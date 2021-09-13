/* Start Header**********************************************************************************/
/*
@file    TransformComponent.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    19/06/2021
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

#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "Engine/Header/Graphic/Graphic.hpp"

#include "Engine/Header/Math/MathLib.hpp"
#include "Engine/Header/ECS/Component/IComponent.hpp"

namespace Engine {
	//Scale value for circle in both axis is same
	struct Transform : public IComponent {
		Math::vec2 position = Math::vec2{}; //x and y for 2d position and z for the layering (whether it appear on top or below)
		Math::vec2 scale = Math::vec2{};
		float angle = float{}; // in degree
		bool isActive = true;
		int layer = 0; //layer which object is placed in higher number is drawn first (they appear behind)

		//Math::mat3 mdl_to_ndc_xform = Math::mat3{};

		inline Math::mat3 GetTransform() const {
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

		Transform() = default;
		Transform(Entity ID, Math::vec2 tPos, Math::vec2 tScale, float rotationAngle, bool active = true, int tLayer = 0) :
			IComponent{ ID },
			position{ tPos }, scale{ tScale }, angle{ rotationAngle },
			isActive{ active }, layer{ tLayer } {}
		Transform(const Transform&) = default;
		Transform& operator=(const Transform&) = default;
	};
}
#endif