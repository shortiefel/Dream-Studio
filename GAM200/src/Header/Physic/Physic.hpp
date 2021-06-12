/*
This file has the functions declaration to be called by the physic system
*/

#ifndef PHYSIC_H
#define PHYSIC_H

namespace Physic {
	struct BoxCollider;
	struct CircleCollider;

	//Collision physic----------------------------------------
	bool isColliding(BoxCollider obj1, BoxCollider obj2);
	bool isColliding(BoxCollider obj1, CircleCollider obj2);
	bool isColliding(CircleCollider obj1, BoxCollider obj2);
	bool isColliding(CircleCollider obj1, CircleCollider obj2);
	//--------------------------------------------------------

	//void applyGravity(); //Vec2 position
}

#endif