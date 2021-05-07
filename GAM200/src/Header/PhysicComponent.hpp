#ifndef PHYSIC_COMPONENT_H
#define PHYSIC_COMPONENT_H

struct BoxCollider {
	unsigned float posX, posY, width, length;
	bool isTrigger = false;
};

struct CircleCollider {
	unsigned float posX, posY, radius;
	bool isTrigger = false;
};


#endif