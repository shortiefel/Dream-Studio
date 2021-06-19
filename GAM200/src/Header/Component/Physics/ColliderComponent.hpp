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
	MathD::Vec2 scale = MathD::Vec2{};

	ColliderType cType = ColliderType::CIRCLE;
	bool isTrigger = false, isActive = true;

	Collider() = default;

	//offsetPosition -> how far away from the transform center
	//offsetScale -> how much it changes the transform scale
	/*Collider(ColliderType c, MathD::Vec2 offsetPosition, MathD::Vec2 offsetScale, bool trigger = false) :
		cType{ c }, pos{ offsetPosition }, scale { offsetScale.x, offsetScale.y }, isTrigger{ trigger } {}

	Collider(ColliderType c, float offsetxPos, float offsetyPos, MathD::Vec2 offsetScale, bool trigger = false) :
		Collider{ c, MathD::Vec2 { offsetxPos, offsetyPos }, offsetScale, trigger } {}

	Collider (ColliderType c, float offsetxPos, float offsetyPos,  float offsetWidth, float offsetHeight, bool trigger = false) :
		Collider{ c, MathD::Vec2 { offsetxPos, offsetyPos }, MathD::Vec2 { offsetWidth, offsetHeight }, trigger } {}*/

	Collider(ColliderType c, bool trigger = false) :
		cType{ c }, pos{ MathD::Vec2{ 0.f, 0.f } }, scale{ MathD::Vec2{ 0.f, 0.f } }, isTrigger{ trigger } {}

	
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