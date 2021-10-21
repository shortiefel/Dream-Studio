/* Start Header**********************************************************************************/
/*
@file    Picking2D.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    23/06/2021
@brief
#include "Engine/Header/Graphic/Picking2D.hpp"
This file include definition for picking checks


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

//#include "Engine/Header/Graphic/Picking2D.hpp"

namespace Engine {
	namespace Graphic {
		//void PickingCheck(Engine::Entity& entity_selected, Math::vec3& mousePos, const Math::vec2& viewportSize, const Math::mat3& inverseCamMatrix) {
		//	mousePos = Math::mat3(2.f / viewportSize.x, 0.f, 0.f,
		//		0.f, 2.f / viewportSize.y, 0.f,
		//		-1.f, -1.f, 1.f) * mousePos;
		//	mousePos = inverseCamMatrix * mousePos;

		//	const auto& transformArray = Engine::DreamECS::GetInstance().GetComponentArrayData<Engine::TransformComponent>();
		//	for (const auto& transform : transformArray) {
		//		const Engine::Entity& entity = transform.GetEntity();
		//		if (Entity_Check(entity)) break;
		//		if (!transform.isActive) continue;

		//		Engine::ColliderComponent collider;
		//		collider.offset_position = Math::vec2{ transform.position };
		//		collider.offset_scale = transform.scale;
		//		collider.angle = transform.angle;
		//		if (Math::epsilonCheck(transform.angle)) {
		//			if (Engine::CollisionImplementation::PointToSquareAABB(Math::vec2{ mousePos.x, mousePos.y }, collider)) {
		//				entity_selected = entity;
		//				//Callback(entity);
		//				std::cout << "calling \n";
		//			}
		//		}

		//		else {
		//			if (Engine::CollisionImplementation::PointToSquareSAT(Math::vec2{ mousePos.x, mousePos.y }, collider)) {
		//				entity_selected = entity;
		//				//Callback(entity);
		//				std::cout << "calling \n";
		//			}
		//		}
		//	}
		//}
	}
}