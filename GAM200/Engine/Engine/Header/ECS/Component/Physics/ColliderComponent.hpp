/* Start Header**********************************************************************************/
/*
@file    ColliderComponent.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    19/06/2021
\brief
This file contain the collider struct to be used by the ECS and various system

//Serialize list
-ColliderType:  ColliderType
-vec2 float:	Position
-vec2 float:    Scale
-bool:			isMoveable
-bool:			isTrigger


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef COLLIDER_COMPONENT_H
#define COLLIDER_COMPONENT_H


#include "Engine/Header/Math/Vector.hpp" //vector 2d

namespace Engine {
	enum class ColliderType {
		CIRCLE = 0,
		SQUARE
	};

	//pos is the world scale position of the object at the top left corner of the object
	//origin is relative position of the object from the pos
	//when origin is 0, object is rotated at the top left corner
	//when origin is w/2, h/2, object is rotated at the center

	struct Collider {

		ColliderType cType = ColliderType::CIRCLE;

		MathD::Vec2 pos = MathD::Vec2{};//, origin;
		MathD::Vec2 scale = MathD::Vec2{};

		bool isTrigger = false, isActive = true;
		//Will be pushed if moveable
		bool isMoveable = false;

		Collider() = default;

		//offsetPosition -> how far away from the transform center
		//offsetScale -> how much it changes the transform scale
		/*Collider(ColliderType c, MathD::Vec2 offsetPosition, MathD::Vec2 offsetScale, bool trigger = false) :
			cType{ c }, pos{ offsetPosition }, scale { offsetScale.x, offsetScale.y }, isTrigger{ trigger } {}

		Collider(ColliderType c, float offsetxPos, float offsetyPos, MathD::Vec2 offsetScale, bool trigger = false) :
			Collider{ c, MathD::Vec2 { offsetxPos, offsetyPos }, offsetScale, trigger } {}

		Collider (ColliderType c, float offsetxPos, float offsetyPos,  float offsetWidth, float offsetHeight, bool trigger = false) :
			Collider{ c, MathD::Vec2 { offsetxPos, offsetyPos }, MathD::Vec2 { offsetWidth, offsetHeight }, trigger } {}*/

		Collider(ColliderType c, bool moveable = false, bool trigger = false) :
			cType{ c }, pos{ MathD::Vec2{ 0.f, 0.f } }, scale{ MathD::Vec2{ 0.f, 0.f } }, isMoveable{ moveable }, isTrigger{ trigger } {}

		//Change of type constructor: Copy an existing Collider but with a different type
		Collider(ColliderType c, MathD::Vec2 tPos, MathD::Vec2 tScale, bool moveable, bool tTrigger) :
			cType{ c }, pos{ tPos }, scale{ tScale }, isMoveable{ moveable }, isTrigger{ tTrigger } {}

		Collider(const Collider&) = default;
		Collider& operator=(const Collider&) = default;
	};
}

#endif