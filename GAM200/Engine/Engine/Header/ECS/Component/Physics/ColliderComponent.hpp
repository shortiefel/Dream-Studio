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


#include "Engine/Header/Math/MathLib.hpp"
#include "Engine/Header/ECS/Component/IComponent.hpp"
#include "Engine/Header/Serialize/Serializer.hpp"

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

		Math::vec2 offset_position = Math::vec2{};//, origin;
		Math::vec2 offset_scale = Math::vec2{};
		float angle = float{};

		bool isTrigger = false, isActive = true;

		Collider Deserialize(const Serializer& serializer);
		void Serialize(const Serializer& serializer);

		Collider() = default;
		//Change of type constructor: Copy an existing Collider but with a different type
		/*Collider(Entity ID, ColliderType c, bool trigger = false);*/
		Collider(Entity ID, ColliderType c = ColliderType::SQUARE, Math::vec2 tPos = Math::vec2{},
			Math::vec2 tScale = Math::vec2{}, float rotation = float{}, bool tTrigger = false, bool active = true);
		Collider(const Collider&) = default;
		Collider& operator=(const Collider&) = default;
	};
}

#endif