/* Start Header**********************************************************************************/
/*
@file    ColliderComponent.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    19/06/2021
@brief
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
#include "Engine/Header/Graphic/Graphic.hpp"

namespace Engine {
	class DSerializer;
	class SSerializer;

	enum class ColliderType {
		CIRCLE = 0,
		SQUARE
	};

	//pos is the world scale position of the object at the top left corner of the object
	//origin is relative position of the object from the pos
	//when origin is 0, object is rotated at the top left corner
	//when origin is w/2, h/2, object is rotated at the center

	struct ColliderComponent : public IComponent {

		ColliderType cType = ColliderType::CIRCLE;

		Math::vec2 offset_position = Math::vec2{};//, origin;
		Math::vec2 offset_scale = Math::vec2{};
		float angle = float{};

		bool isTrigger = false, isActive = true;

		ColliderComponent& Deserialize(const DSerializer& _serializer);
		void Serialize(const SSerializer& _serializer);
		std::map<std::string, GraphicImplementation::GLModel>::iterator stencil_ref;

		//offsetPosition -> how far away from the transform center
		//offsetScale -> how much it changes the transform scale
		/*Collider(ColliderType c, Math::vec2 offsetPosition, Math::vec2 offsetScale, bool trigger = false) :
			cType{ c }, pos{ offsetPosition }, scale { offsetScale.x, offsetScale.y }, isTrigger{ trigger } {}

		Collider(ColliderType c, float offsetxPos, float offsetyPos, Math::vec2 offsetScale, bool trigger = false) :
			Collider{ c, Math::vec2 { offsetxPos, offsetyPos }, offsetScale, trigger } {}

		Collider (ColliderType c, float offsetxPos, float offsetyPos,  float offsetWidth, float offsetHeight, bool trigger = false) :
			Collider{ c, Math::vec2 { offsetxPos, offsetyPos }, Math::vec2 { offsetWidth, offsetHeight }, trigger } {}*/

		ColliderComponent(ColliderType c, bool moveable = false, bool trigger = false, std::string stencil = "stencilBox") :
			cType{ c }, offset_position{ Math::vec2{ 0.f, 0.f } }, offset_scale{ Math::vec2{ 0.f, 0.f } }, isTrigger{ trigger } {}//, stencil_ref{ GraphicImplementation::models.find(stencil) }{}

		//Change of type constructor: Copy an existing Collider but with a different type
		/*Collider(Entity ID, ColliderType c, bool trigger = false);*/
		ColliderComponent(Entity _ID = Entity{}, ColliderType _c = ColliderType::SQUARE, Math::vec2 _pos = Math::vec2{},
			Math::vec2 _scale = Math::vec2{}, float _rotation = float{}, bool _trigger = false, bool _active = true);
		ColliderComponent(const ColliderComponent&) = default;
		ColliderComponent& operator=(const ColliderComponent&) = default;
	};
}

#endif