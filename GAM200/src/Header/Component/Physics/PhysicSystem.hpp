#ifndef PHYSIC_SYSTEM_H
#define PHYSIC_SYSTEM_H

#include "Component/ComponentArray.hpp"
#include "pch.hpp"

class PhysicSystem {
public:
	static void Create();
	static PhysicSystem* Get();
	static void Destroy();
	void Update();
private:
	float gravity = 10.f;
	static PhysicSystem* s_instance;

	std::set<Entity> mEntities;
};

#endif