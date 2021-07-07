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
struct Collider;
struct Transform;
#include "Math/MathLib.hpp"

namespace PhysicImplementation {
	//Collision physic----------------------------------------
	bool isColliding(MathD::Vec2& dir, const Collider& obj1, const Collider& obj2);
	bool isCollidingSQUAREtoSQUARE(MathD::Vec2& dir, const Collider& obj1, const Collider& obj2);
	bool isCollidingSQUAREtoCIRCLE(MathD::Vec2& dir, const Collider& obj1, const Collider& obj2);
	bool isCollidingCIRCLEtoSQUARE(MathD::Vec2& dir, const Collider& obj1, const Collider& obj2);
	bool isCollidingCIRCLEtoCIRCLE(MathD::Vec2& dir, const Collider& obj1, const Collider& obj2);

	void CollisionResolution(MathD::Vec2& dir, Transform& trans1, const Collider& col1, Transform& trans2, const Collider& col2);
	void CollisionResolutionSQUAREtoSQUARE(MathD::Vec2& dir, Transform& trans1, const Collider& col1, Transform& trans2, const Collider& col2);
	void CollisionResolutionSQUAREtoCIRCLE(MathD::Vec2& dir, Transform& trans1, const Collider& col1, Transform& trans2, const Collider& col2);
	void CollisionResolutionCIRCLEtoSQUARE(MathD::Vec2& dir, Transform& trans1, const Collider& col1, Transform& trans2, const Collider& col2);
	void CollisionResolutionCIRCLEtoCIRCLE(MathD::Vec2& dir, Transform& trans1, const Collider& col1, Transform& trans2, const Collider& col2);
	//--------------------------------------------------------

	//void applyGravity(); //Vec2 position
}

#endif