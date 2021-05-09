#ifndef RIGIDBODY_H
#define RIGIDBODY_H

struct RigidBody {
	//Gravity will be applied by default when rigidbody is applied
	//object cannot be pushed by default
	bool hasGravity = true, isMoveable = false;

};

#endif