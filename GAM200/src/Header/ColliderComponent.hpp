#ifndef COLLIDER_COMPONENT_H
#define COLLIDER_COMPONENT_H

#include "Math/Vector2D.hpp"

enum class CollisionType {
	CIRCLE = 0,
	BOX
};

//pos is the world scale position of the object at the top left corner of the object
//origin is relative position of the object from the pos
//when origin is 0, object is rotated at the top left corner
//when origin is w/2, h/2, object is rotated at the center

struct Collider {
	Vec2 pos;//, origin;
	CollisionType cType;
	bool isTrigger = false, isActive = true;

	Collider (float xPos, float yPos, CollisionType c, bool istrigger = false) :
		pos{ xPos, yPos }, cType{ c }, isTrigger{ istrigger } {}
	void SetActive(bool t) { isActive = t; }
};

struct BoxCollider : Collider {
	float w, h;

	BoxCollider (float xPos, float yPos, float width, float height, bool istrigger = false) : 
		 w{ width }, h{ height }, Collider { xPos, yPos, CollisionType::BOX, istrigger } {}
	BoxCollider(Vec2 position, float width, float height, bool istrigger = false) :
		BoxCollider { position.x, position.y, width, height , istrigger } {}
};

struct CircleCollider : Collider {
	float r;

	CircleCollider(float xPos, float yPos, float radius, bool istrigger = false) :
		r { radius }, Collider{ xPos, yPos, CollisionType::CIRCLE, istrigger } {}
	CircleCollider(Vec2 position, float radius, bool istrigger = false) :
		CircleCollider{ position.x, position.y, radius, istrigger } {}
};


#endif