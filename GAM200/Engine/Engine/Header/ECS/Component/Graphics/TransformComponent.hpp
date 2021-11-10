/* Start Header**********************************************************************************/
/*
@file    TransformComponent.hpp
@author  Chia Yi Da		c.yida@digipen.edu
@date    19/06/2021
@brief
This file contains the TransformComponent declaration


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "Engine/Header/ECS/Component/IComponent.hpp"
#include "Engine/Header/Math/MathLib.hpp"

namespace Engine
{
	class DSerializer;
	class SSerializer;

	struct TransformComponent : public IComponent {
		Math::vec2 position{};		// True position 
		Math::vec2 localPosition{}; // Local  position(to be displayed and can be same as true position)

		Math::vec2 scale{};		// Can be scaled; xy -> Circle in both axis is same

		float angle{};	// In degrees
		int layer = 2;	// Higher number -> rendered last

		bool isActive = true;


		TransformComponent(Entity_id _ID = DEFAULT_ENTITY_ID, Math::vec2 _pos = Math::vec2{},
			Math::vec2 _scale = Math::vec2{ 1.f, 1.f }, float _angle = 0.f,
			int _layer = 2, bool _active = true);


		TransformComponent& Deserialize(const DSerializer& _serializer);
		void Serialize(const SSerializer& _serializer);

		TransformComponent(const TransformComponent&) = default;

		TransformComponent& operator=(const TransformComponent&) = default;
		TransformComponent& operator+=(const TransformComponent& _rhs);
	};
}
#endif

// Code that might be used for the future

/*
Math::vec2 GetTruePosition() const;

Math::mat3 GetTransform() const;
*/

/*
Transform(Transform&& rhs) noexcept {
	position = std::move(rhs.position);
	scale = std::move(rhs.scale);
	angle = std::move(rhs.angle);
	isActive = std::move(rhs.isActive);
	layer = std::move(rhs.layer);
	SetEntityId(rhs.GetEntity());
	rhs.SetEntityId(DEFAULT_ENTITY);
}
*/