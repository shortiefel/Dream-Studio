#ifndef COLLISION_COMPONENT_H
#define COLLISION_COMPONENT_H



struct BoxCollider {
	float x, y, w, h;
	bool isTrigger = false;
};

struct CircleCollider {
	float x, y, r;
	bool isTrigger = false;
};


#endif