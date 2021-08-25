/* Start Header**********************************************************************************/
/*
@file    Physic.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    19/06/2021
\brief
This file has the functions declaration to be called by the physic system


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/


#ifndef PHYSIC_H
#define PHYSIC_H

//#include "Component/Physics/ColliderComponent.hpp"
//#include "Component/Graphics/TransformComponent.hpp"
#include <glm/glm.hpp>

namespace Engine {
	struct Collider; //Forward declaration
	struct Transform; //Forward declaration

	namespace PhysicImplementation {
		//Collision physic----------------------------------------
		bool isColliding(glm::vec2& dir, const Collider& obj1, const Collider& obj2);
		bool isCollidingSQUAREtoSQUARE(glm::vec2& dir, const Collider& obj1, const Collider& obj2);
		bool isCollidingSQUAREtoCIRCLE(glm::vec2& dir, const Collider& obj1, const Collider& obj2);
		bool isCollidingCIRCLEtoSQUARE(glm::vec2& dir, const Collider& obj1, const Collider& obj2);
		bool isCollidingCIRCLEtoCIRCLE(glm::vec2& dir, const Collider& obj1, const Collider& obj2);

		void CollisionResolution(glm::vec2& dir, Transform& trans1, const Collider& col1, Transform& trans2, const Collider& col2);
		void CollisionResolutionSQUAREtoSQUARE(glm::vec2& dir, Transform& trans1, const Collider& col1, Transform& trans2, const Collider& col2);
		void CollisionResolutionSQUAREtoCIRCLE(glm::vec2& dir, Transform& trans1, const Collider& col1, Transform& trans2, const Collider& col2);
		void CollisionResolutionCIRCLEtoSQUARE(glm::vec2& dir, Transform& trans1, const Collider& col1, Transform& trans2, const Collider& col2);
		void CollisionResolutionCIRCLEtoCIRCLE(glm::vec2& dir, Transform& trans1, const Collider& col1, Transform& trans2, const Collider& col2);
		//--------------------------------------------------------

		//void applyGravity(); //Vec2 position
	}
}

#endif