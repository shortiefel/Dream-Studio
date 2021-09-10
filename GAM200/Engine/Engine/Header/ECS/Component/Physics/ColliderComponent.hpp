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
#include "Engine/Header/ECS/Component/IComponent.hpp"

namespace Engine {
	enum class ColliderType {
		CIRCLE = 0,
		SQUARE
	};

	//pos is the world scale position of the object at the top left corner of the object
	//origin is relative position of the object from the pos
	//when origin is 0, object is rotated at the top left corner
	//when origin is w/2, h/2, object is rotated at the center

	struct Collider : public IComponent {

		ColliderType cType = ColliderType::CIRCLE;

		glm::vec2 offset_position = glm::vec2{};//, origin;
		glm::vec2 offset_scale = glm::vec2{};
		float angle = float{};

		bool isTrigger = false, isActive = true;

		Collider() = default;

		Collider(Entity ID, ColliderType c, bool trigger = false) :
			IComponent{ ID }, cType{ c }, offset_position{ glm::vec2{ 0.f, 0.f } }, offset_scale{ glm::vec2{ 0.f, 0.f } }, angle{ 0.f }, isTrigger{ trigger } {}

		//Change of type constructor: Copy an existing Collider but with a different type
		Collider(Entity ID, ColliderType c, glm::vec2 tPos, glm::vec2 tScale, float rotation, bool tTrigger, bool active = true) :
			IComponent{ ID }, cType{ c }, offset_position{ tPos }, offset_scale{ tScale }, angle{ rotation }, isTrigger{ tTrigger }, isActive{ active } {}

		Collider(const Collider&) = default;
		Collider& operator=(const Collider&) = default;
	};
}

#endif