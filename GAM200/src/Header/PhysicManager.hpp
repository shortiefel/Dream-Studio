#ifndef PHYSIC_MANAGER_H
#define PHYSIC_MANAGER_H

#include "Component/ComponentArray.hpp"

class PhysicManager {
public:
	static void Create();
	static PhysicManager* Get();
	static void Destroy();
	static void Run();
private:
	float gravity = 10.f;
	static PhysicManager* s_instance;
};

#endif