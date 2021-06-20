/* Start Header**********************************************************************************/
/*
@file    Physic.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    19/06/2021
\brief
This file has the functions declaration to be called by the physic system

*/
/* End Header **********************************************************************************/


#ifndef PHYSIC_H
#define PHYSIC_H

#include "Component/Physics/ColliderComponent.hpp"
#include "Component/Graphics/TransformComponent.hpp"

namespace PhysicImplementation {
	//Collision physic----------------------------------------
	bool isColliding(const Collider& obj1, const Collider& obj2);
	bool isCollidingBOXtoBOX(const Collider& obj1, const Collider& obj2);
	bool isCollidingBOXtoCIRCLE(const Collider& obj1, const Collider& obj2);
	bool isCollidingCIRCLEtoBOX(const Collider& obj1, const Collider& obj2);
	bool isCollidingCIRCLEtoCIRCLE(const Collider& obj1, const Collider& obj2);

	void CollisionResolution(Transform& trans1, const Collider& col1, Transform& trans2, const Collider& col2);
	void CollisionResolutionBOXtoBOX(Transform& trans1, const Collider& col1, Transform& trans2, const Collider& col2);
	void CollisionResolutionBOXtoCIRCLE(Transform& trans1, const Collider& col1, Transform& trans2, const Collider& col2);
	void CollisionResolutionCIRCLEtoBOX(Transform& trans1, const Collider& col1, Transform& trans2, const Collider& col2);
	void CollisionResolutionCIRCLEtoCIRCLE(Transform& trans1, const Collider& col1, Transform& trans2, const Collider& col2);
	//--------------------------------------------------------

	//void applyGravity(); //Vec2 position
}

#endif