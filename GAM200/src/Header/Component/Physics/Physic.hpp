#ifndef PHYSIC_H
#define PHYSIC_H

struct BoxCollider;
struct CircleCollider;

//Collision physic----------------------------------------
bool isColliding(BoxCollider obj1, BoxCollider obj2);
bool isColliding(BoxCollider obj1, CircleCollider obj2);
bool isColliding(CircleCollider obj1, BoxCollider obj2);
bool isColliding(CircleCollider obj1, CircleCollider obj2);
//--------------------------------------------------------

//void applyGravity(); //Vec2 position

#endif