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


#include <glm/glm.hpp>

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

		glm::vec2 offset_position = glm::vec2{};//, origin;
		glm::vec2 offset_scale = glm::vec2{};

		bool isTrigger = false, isActive = true;
		//Will be pushed if moveable
		bool isMoveable = false;

		Collider() = default;

		Collider(ColliderType c, bool moveable = false, bool trigger = false) :
			cType{ c }, offset_position{ glm::vec2{ 0.f, 0.f } }, offset_scale{ glm::vec2{ 0.f, 0.f } }, isMoveable{ moveable }, isTrigger{ trigger } {}

		//Change of type constructor: Copy an existing Collider but with a different type
		Collider(ColliderType c, glm::vec2 tPos, glm::vec2 tScale, bool moveable, bool tTrigger) :
			cType{ c }, offset_position{ tPos }, offset_scale{ tScale }, isMoveable{ moveable }, isTrigger{ tTrigger } {}

		Collider(const Collider&) = default;
		Collider& operator=(const Collider&) = default;
	};
}

#endif