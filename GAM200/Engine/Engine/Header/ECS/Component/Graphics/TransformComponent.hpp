/* Start Header**********************************************************************************/
/*
@file    TransformComponent.hpp
@author  Chia Yi Da		chiayida98@gmail.com
@date    19/06/2021
@brief
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


namespace Engine 
{
	class DSerializer;
	class SSerializer;

	//Scale value for circle in both axis is same
	struct TransformComponent : public IComponent {
		Math::vec2 position = Math::vec2{};
		Math::vec2 scale = Math::vec2{};
		float angle = float{}; // degrees
		bool isActive = true;
		int layer = 2; // higher number = on top

		TransformComponent& Deserialize(const DSerializer& _serializer);
		void Serialize(const SSerializer& _serializer);

		Math::vec2 GetTruePosition() const;

		TransformComponent(Entity_id _ID = DEFAULT_ENTITY_ID, Math::vec2 _pos = Math::vec2{}, Math::vec2 _scale = Math::vec2{1,1},
			float _angle = float{}, bool _active = true, int _layer = 2);
		TransformComponent& operator+= (const TransformComponent& _rhs);

		TransformComponent(const TransformComponent&) = default;
		TransformComponent& operator=(const TransformComponent&) = default;
	};
}
#endif




//Math::mat3 GetTransform() const;

/*Transform(Transform&& rhs) noexcept {
	position = std::move(rhs.position);
	scale = std::move(rhs.scale);
	angle = std::move(rhs.angle);
	isActive = std::move(rhs.isActive);
	layer = std::move(rhs.layer);
	SetEntityId(rhs.GetEntity());
	rhs.SetEntityId(DEFAULT_ENTITY);
}*/