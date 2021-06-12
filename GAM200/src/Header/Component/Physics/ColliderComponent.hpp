#ifndef COLLIDER_COMPONENT_H
#define COLLIDER_COMPONENT_H


#include "Math/Vector.hpp" //vector 2d


enum class ColliderType {
	CIRCLE = 0,
	BOX
};

//pos is the world scale position of the object at the top left corner of the object
//origin is relative position of the object from the pos
//when origin is 0, object is rotated at the top left corner
//when origin is w/2, h/2, object is rotated at the center

struct Collider {

	MathD::Vec2 pos = MathD::Vec2{};//, origin;
	float w = float{}, h = float{};

	ColliderType cType = ColliderType::CIRCLE;
	bool isTrigger = false, isActive = true;

	Collider() = default;
	Collider (float xPos, float yPos, ColliderType c, float wVal, float hVal = 0, bool istrigger = false) :
		pos{ xPos, yPos }, cType{ c }, w{ wVal }, h{ hVal }, isTrigger{ istrigger } {}
	//void SetActive(bool t) { isActive = t; }
};

//struct BoxCollider : Collider {
//	float w, h;
//
//	BoxCollider (float xPos, float yPos, float width, float height, bool istrigger = false) : 
//		 w{ width }, h{ height }, Collider { xPos, yPos, ColliderType::BOX, istrigger } {}
//
//	BoxCollider(MathD::Vec2 position, float width, float height, bool istrigger = false) :
//
//		BoxCollider { position.x, position.y, width, height , istrigger } {}
//};
//
//struct CircleCollider : Collider {
//	float r;
//
//	CircleCollider(float xPos, float yPos, float radius, bool istrigger = false) :
//		r { radius }, Collider{ xPos, yPos, ColliderType::CIRCLE, istrigger } {}
//
//	CircleCollider(MathD::Vec2 position, float radius, bool istrigger = false) :
//
//		CircleCollider{ position.x, position.y, radius, istrigger } {}
//};


#endif