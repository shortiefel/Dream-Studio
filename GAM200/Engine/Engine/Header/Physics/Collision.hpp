/* Start Header**********************************************************************************/
/*
@file    Collision.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu		100%
@date    19/06/2021
\brief
#include "Engine/Header/Physics/Collision.hpp"
This file has the functions declaration to be called by the physic system


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/


#ifndef COLLISION_H
#define COLLISION_H

#include "Engine/Header/Math/MathLib.hpp"
#include "Engine/Header/Physics/Ray.hpp"

#include <limits>

namespace Engine {
	struct ColliderComponent; //Forward declaration
	struct TransformComponent; //Forward declaration

	struct RaycastHit {
		float distance = (std::numeric_limits<float>::max)();
		Math::vec2 point;
		//Negative for no hit
		int entity_id = -1;
	};

	//REMEMBER TO CHANGE to Collision
	namespace CollisionImplementation {
		//Collision physic----------------------------------------
		bool isColliding(Math::vec2& dir, const ColliderComponent& obj1, bool ent1Moveable, const ColliderComponent& obj2, bool ent2Moveable);
		/*
		Shape 1's diagonal (center to one corner) is checked with Shape 2's edge (Repeated for all diagonal to all edge)
		Shape 1 and Shape 2 switch position and is checked again
		*/
		bool isCollidingSquaretoSquare(Math::vec2& dir, const ColliderComponent& obj1, const ColliderComponent& obj2);
		bool isCollidingSquaretoCircle(Math::vec2& dir, const ColliderComponent& obj1, const ColliderComponent& obj2);
		bool isCollidingCircletoSquare(Math::vec2& dir, const ColliderComponent& obj1, const ColliderComponent& obj2);
		bool isCollidingCircletoCircle(Math::vec2& dir, const ColliderComponent& obj1, const ColliderComponent& obj2);

		void CollisionResolution(Math::vec2& dir, TransformComponent& trans1, const ColliderComponent& col1, TransformComponent& trans2, const ColliderComponent& col2);
		void CollisionResolutionMain(Math::vec2& dir, TransformComponent& trans1, const ColliderComponent& col1, TransformComponent& trans2, const ColliderComponent& col2);
		//void CollisionResolutionSquaretoSquare(Math::vec2& dir, Transform& trans1, const Collider& col1, Transform& trans2, const Collider& col2);
		//void CollisionResolutionSquaretoCircle(Math::vec2& dir, Transform& trans1, const Collider& col1, Transform& trans2, const Collider& col2);
		//void CollisionResolutionCircletoSquare(Math::vec2& dir, Transform& trans1, const Collider& col1, Transform& trans2, const Collider& col2);
		void CollisionResolutionCircletoCircle(Math::vec2& dir, TransformComponent& trans1, const ColliderComponent& col1, TransformComponent& trans2, const ColliderComponent& col2);
		//--------------------------------------------------------

		bool PointToSquareAABB(const Math::vec2& pt, const ColliderComponent& obj);
		bool PointToSquareSAT(const Math::vec2& pt, const ColliderComponent& obj);

		bool RayCast_Internal(const Engine::Ray& ray, const TransformComponent& transform, const ColliderComponent& collider, RaycastHit* hit);
	}
}

#endif