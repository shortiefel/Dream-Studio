/* Start Header**********************************************************************************/
/*
@file    Collision.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    19/06/2021
\brief
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

namespace Engine {
	struct ColliderComponent; //Forward declaration
	struct TransformComponent; //Forward declaration

	namespace CollisionImplementation {
		//Collision physic----------------------------------------
		bool isColliding(Math::vec2& dir, const ColliderComponent& obj1, bool ent1Moveable, const ColliderComponent& obj2, bool ent2Moveable);
		/*
		Shape 1's diagonal (center to one corner) is checked with Shape 2's edge (Repeated for all diagonal to all edge)
		Shape 1 and Shape 2 switch position and is checked again
		*/
		bool isCollidingSQUAREtoSQUARE(Math::vec2& dir, const ColliderComponent& obj1, const ColliderComponent& obj2);
		bool isCollidingSQUAREtoCIRCLE(Math::vec2& dir, const ColliderComponent& obj1, const ColliderComponent& obj2);
		bool isCollidingCIRCLEtoSQUARE(Math::vec2& dir, const ColliderComponent& obj1, const ColliderComponent& obj2);
		bool isCollidingCIRCLEtoCIRCLE(Math::vec2& dir, const ColliderComponent& obj1, const ColliderComponent& obj2);

		void CollisionResolution(Math::vec2& dir, TransformComponent& trans1, const ColliderComponent& col1, TransformComponent& trans2, const ColliderComponent& col2);
		void CollisionResolutionMain(Math::vec2& dir, TransformComponent& trans1, const ColliderComponent& col1, TransformComponent& trans2, const ColliderComponent& col2);
		//void CollisionResolutionSQUAREtoSQUARE(Math::vec2& dir, Transform& trans1, const Collider& col1, Transform& trans2, const Collider& col2);
		//void CollisionResolutionSQUAREtoCIRCLE(Math::vec2& dir, Transform& trans1, const Collider& col1, Transform& trans2, const Collider& col2);
		//void CollisionResolutionCIRCLEtoSQUARE(Math::vec2& dir, Transform& trans1, const Collider& col1, Transform& trans2, const Collider& col2);
		void CollisionResolutionCIRCLEtoCIRCLE(Math::vec2& dir, TransformComponent& trans1, const ColliderComponent& col1, TransformComponent& trans2, const ColliderComponent& col2);
		//--------------------------------------------------------

		//void applyGravity(); //Vec2 position
	}
}

#endif