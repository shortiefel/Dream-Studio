/* Start Header**********************************************************************************/
/*
@file    Picking2D.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    23/06/2021
@brief
#include "Engine/Header/Graphic/Picking2D.hpp"
This file include declaration for picking checks


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef PICKING_2D_H
#define PICKING_2D_H

#include "Engine/Header/Math/MathLib.hpp"
#include "Engine/Header/ECS/DreamECS.hpp"

#include "Engine/Header/ECS/Component/ComponentArray.hpp"

#include "Engine/Header/ECS/Component/Graphics/TransformComponent.hpp"
#include "Engine/Header/ECS/Component/Physics/ColliderComponent.hpp"
#include "Engine/Header/Physics/Collision.hpp"

namespace Engine {
	namespace Graphic {
		//false = no hover, true = hover
		void RecordMouseOverlap(Entity_id entity_id, bool type);

		//Callback is called when mouse is over entity while CallbackFail is called when there is no hover for the entity
		template<typename Func, typename Func2>
		void PickingCheck(Math::vec3& mousePos, const Math::vec2& viewportSize, const Math::mat3& inverseCamMatrix, Func Callback, Func2 CallbackFail) {
			mousePos = Math::mat3(2.f / viewportSize.x, 0.f, 0.f,
				0.f, 2.f / viewportSize.y, 0.f,
				-1.f, -1.f, 1.f) * mousePos;
			mousePos = inverseCamMatrix * mousePos;

			const auto& transformArray = Engine::DreamECS::GetInstance().GetComponentArrayData<Engine::TransformComponent>();
			for (const auto& transform : transformArray) {
				const Engine::Entity& entity = transform.GetEntity();
				if (Entity_Check(entity)) break;
				if (!transform.isActive) continue;

				Engine::ColliderComponent collider;
				collider.offset_position = Math::vec2{ transform.position };
				collider.offset_scale = transform.scale;
				collider.angle = transform.angle;
				if (Math::epsilonCheck(transform.angle)) {
					if (Engine::CollisionImplementation::PointToSquareAABB(Math::vec2{ mousePos.x, mousePos.y }, collider)) {
						Callback(entity);
					}
					else {
						CallbackFail(entity);
					}
				}

				else {
					if (Engine::CollisionImplementation::PointToSquareSAT(Math::vec2{ mousePos.x, mousePos.y }, collider)) {
						Callback(entity);
					}
					else {
						CallbackFail(entity);
					}
				}
			}
		}
	}
}

#endif